/*
 *  Copyright (C) 1999-2000 Harri Porten (porten@kde.org)
 *  Copyright (C) 2004, 2005, 2006, 2007, 2008 Apple Inc. All rights reserved.
 *  Copyright (C) 2014 FactorY Media Production GmbH
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 *  USA
 *
 */

#include "config.h"
#include "DateConstructor.h"

#include "DateConversion.h"
#include "DateInstance.h"
#include "DatePrototype.h"
#include "JSFunction.h"
#include "JSGlobalObject.h"
#include "JSString.h"
#include "JSStringBuilder.h"
#include "ObjectPrototype.h"
#include "PrototypeFunction.h"
#include <math.h>
#include <time.h>
#include <wtf/DateMath.h>
#include <wtf/MathExtras.h>

#if OS(WINCE) && !PLATFORM(QT)
extern "C" time_t time(time_t* timer); // Provided by libce.
#endif

#if HAVE(SYS_TIME_H)
#include <sys/time.h>
#endif

#if HAVE(SYS_TIMEB_H)
#include <sys/timeb.h>
#endif

using namespace WTF;

namespace JSC {

ASSERT_CLASS_FITS_IN_CELL(DateConstructor);

static EncodedJSValue JSC_HOST_CALL dateParse(ExecState*);
static EncodedJSValue JSC_HOST_CALL dateNow(ExecState*);
static EncodedJSValue JSC_HOST_CALL dateUTC(ExecState*);

DateConstructor::DateConstructor(ExecState* exec, JSGlobalObject* globalObject, NonNullPassRefPtr<Structure> structure, Structure* prototypeFunctionStructure, DatePrototype* datePrototype)
    : InternalFunction(&exec->globalData(), globalObject, structure, Identifier(exec, datePrototype->classInfo()->className))
{
      putDirectWithoutTransition(exec->propertyNames().prototype, datePrototype, DontEnum|DontDelete|ReadOnly);

      putDirectFunctionWithoutTransition(exec, new (exec) NativeFunctionWrapper(exec, globalObject, prototypeFunctionStructure, 1, exec->propertyNames().parse, dateParse), DontEnum);
      putDirectFunctionWithoutTransition(exec, new (exec) NativeFunctionWrapper(exec, globalObject, prototypeFunctionStructure, 7, exec->propertyNames().UTC, dateUTC), DontEnum);
      putDirectFunctionWithoutTransition(exec, new (exec) NativeFunctionWrapper(exec, globalObject, prototypeFunctionStructure, 0, exec->propertyNames().now, dateNow), DontEnum);

      putDirectWithoutTransition(exec->propertyNames().length, jsNumber(exec, 7), ReadOnly | DontEnum | DontDelete);
}

// ECMA 15.9.3
JSObject* constructDate(ExecState* exec, const ArgList& args)
{
    int numArgs = args.size();

    double value;

    if (numArgs == 0) // new Date() ECMA 15.9.3.3
		{
        value = jsCurrentTime();
/* FYWEBKITMOD BEGIN implementing offset to be used to correct time returned by new Date() */
		DateInstance* obj = new (exec) DateInstance(exec, value);
		JSValue    offset = obj->prototype().get(exec, Identifier(exec, "userTimeOffset"));

		if (offset.isNumber())
			{
			double dOffset = 0.0;
			offset.getNumber(dOffset);
			value += dOffset;
			}

		obj->setInternalValue(jsNumber(exec, timeClip(value)));
		return obj;
/* FYWEBKITMOD END */
		}
    else if (numArgs == 1) {
        if (args.at(0).inherits(&DateInstance::info))
            value = asDateInstance(args.at(0))->internalNumber();
        else {
            JSValue primitive = args.at(0).toPrimitive(exec);
            if (primitive.isString())
                value = parseDate(exec, primitive.getString(exec));
            else
                value = primitive.toNumber(exec);
        }
    } else {
        if (isnan(args.at(0).toNumber(exec))
                || isnan(args.at(1).toNumber(exec))
                || (numArgs >= 3 && isnan(args.at(2).toNumber(exec)))
                || (numArgs >= 4 && isnan(args.at(3).toNumber(exec)))
                || (numArgs >= 5 && isnan(args.at(4).toNumber(exec)))
                || (numArgs >= 6 && isnan(args.at(5).toNumber(exec)))
                || (numArgs >= 7 && isnan(args.at(6).toNumber(exec))))
            value = NaN;
        else {
            GregorianDateTime t;
            int year = args.at(0).toInt32(exec);
            t.year = (year >= 0 && year <= 99) ? year : year - 1900;
            t.month = args.at(1).toInt32(exec);
            t.monthDay = (numArgs >= 3) ? args.at(2).toInt32(exec) : 1;
            t.hour = args.at(3).toInt32(exec);
            t.minute = args.at(4).toInt32(exec);
            t.second = args.at(5).toInt32(exec);
            t.isDST = -1;
            double ms = (numArgs >= 7) ? args.at(6).toNumber(exec) : 0;
            value = gregorianDateTimeToMS(exec, t, ms, false);
        }
    }

    return new (exec) DateInstance(exec, value);
}

static EncodedJSValue JSC_HOST_CALL constructWithDateConstructor(ExecState* exec)
{
    ArgList args(exec);
    return JSValue::encode(constructDate(exec, args));
}

ConstructType DateConstructor::getConstructData(ConstructData& constructData)
{
    constructData.native.function = constructWithDateConstructor;
    return ConstructTypeHost;
}

// ECMA 15.9.2
static EncodedJSValue JSC_HOST_CALL callDate(ExecState* exec)
{
    time_t localTime = time(0);
    tm localTM;
    getLocalTime(&localTime, &localTM);
    GregorianDateTime ts(exec, localTM);
    DateConversionBuffer date;
    DateConversionBuffer time;
    formatDate(ts, date);
    formatTime(ts, time);
    return JSValue::encode(jsMakeNontrivialString(exec, date, " ", time));
}

CallType DateConstructor::getCallData(CallData& callData)
{
    callData.native.function = callDate;
    return CallTypeHost;
}

static EncodedJSValue JSC_HOST_CALL dateParse(ExecState* exec)
{
    return JSValue::encode(jsNumber(exec, parseDate(exec, exec->argument(0).toString(exec))));
}

static EncodedJSValue JSC_HOST_CALL dateNow(ExecState* exec)
{
    return JSValue::encode(jsNumber(exec, jsCurrentTime()));
}

static EncodedJSValue JSC_HOST_CALL dateUTC(ExecState* exec) 
{
    int n = exec->argumentCount();
    if (isnan(exec->argument(0).toNumber(exec))
            || isnan(exec->argument(1).toNumber(exec))
            || (n >= 3 && isnan(exec->argument(2).toNumber(exec)))
            || (n >= 4 && isnan(exec->argument(3).toNumber(exec)))
            || (n >= 5 && isnan(exec->argument(4).toNumber(exec)))
            || (n >= 6 && isnan(exec->argument(5).toNumber(exec)))
            || (n >= 7 && isnan(exec->argument(6).toNumber(exec))))
        return JSValue::encode(jsNaN(exec));

    GregorianDateTime t;
    int year = exec->argument(0).toInt32(exec);
    t.year = (year >= 0 && year <= 99) ? year : year - 1900;
    t.month = exec->argument(1).toInt32(exec);
    t.monthDay = (n >= 3) ? exec->argument(2).toInt32(exec) : 1;
    t.hour = exec->argument(3).toInt32(exec);
    t.minute = exec->argument(4).toInt32(exec);
    t.second = exec->argument(5).toInt32(exec);
    double ms = (n >= 7) ? exec->argument(6).toNumber(exec) : 0;
    return JSValue::encode(jsNumber(exec, timeClip(gregorianDateTimeToMS(exec, t, ms, true))));
}

} // namespace JSC
