/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"

#if ENABLE(SHARED_WORKERS)

#include "JSSharedWorker.h"

#include "JSMessagePort.h"
#include "MessagePort.h"
#include "SharedWorker.h"
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSharedWorker);

/* Hash table */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSSharedWorkerTableValues[3] =
{
    { "port", DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSharedWorkerPort), (intptr_t)0 THUNK_GENERATOR(0) },
    { "constructor", DontEnum | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSharedWorkerConstructor), (intptr_t)0 THUNK_GENERATOR(0) },
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSSharedWorkerTable = { 4, 3, JSSharedWorkerTableValues, 0 };
/* Hash table for constructor */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSSharedWorkerConstructorTableValues[1] =
{
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSSharedWorkerConstructorTable = { 1, 0, JSSharedWorkerConstructorTableValues, 0 };
const ClassInfo JSSharedWorkerConstructor::s_info = { "SharedWorkerConstructor", 0, &JSSharedWorkerConstructorTable, 0 };

JSSharedWorkerConstructor::JSSharedWorkerConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
    : DOMConstructorObject(JSSharedWorkerConstructor::createStructure(globalObject->objectPrototype()), globalObject)
{
    putDirect(exec->propertyNames().prototype, JSSharedWorkerPrototype::self(exec, globalObject), DontDelete | ReadOnly);
    putDirect(exec->propertyNames().length, jsNumber(exec, 2), ReadOnly | DontDelete | DontEnum);
}

bool JSSharedWorkerConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSharedWorkerConstructor, DOMObject>(exec, &JSSharedWorkerConstructorTable, this, propertyName, slot);
}

bool JSSharedWorkerConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSharedWorkerConstructor, DOMObject>(exec, &JSSharedWorkerConstructorTable, this, propertyName, descriptor);
}

ConstructType JSSharedWorkerConstructor::getConstructData(ConstructData& constructData)
{
    constructData.native.function = constructJSSharedWorker;
    return ConstructTypeHost;
}

/* Hash table for prototype */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSSharedWorkerPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSSharedWorkerPrototypeTable = { 1, 0, JSSharedWorkerPrototypeTableValues, 0 };
const ClassInfo JSSharedWorkerPrototype::s_info = { "SharedWorkerPrototype", 0, &JSSharedWorkerPrototypeTable, 0 };

JSObject* JSSharedWorkerPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSharedWorker>(exec, globalObject);
}

const ClassInfo JSSharedWorker::s_info = { "SharedWorker", &JSAbstractWorker::s_info, &JSSharedWorkerTable, 0 };

JSSharedWorker::JSSharedWorker(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<SharedWorker> impl)
    : JSAbstractWorker(structure, globalObject, impl)
{
}

JSObject* JSSharedWorker::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSharedWorkerPrototype(globalObject, JSSharedWorkerPrototype::createStructure(JSAbstractWorkerPrototype::self(exec, globalObject)));
}

bool JSSharedWorker::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSharedWorker, Base>(exec, &JSSharedWorkerTable, this, propertyName, slot);
}

bool JSSharedWorker::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSharedWorker, Base>(exec, &JSSharedWorkerTable, this, propertyName, descriptor);
}

JSValue jsSharedWorkerPort(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSharedWorker* castedThis = static_cast<JSSharedWorker*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SharedWorker* imp = static_cast<SharedWorker*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->port()));
    return result;
}

JSValue jsSharedWorkerConstructor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSharedWorker* domObject = static_cast<JSSharedWorker*>(asObject(slotBase));
    return JSSharedWorker::getConstructor(exec, domObject->globalObject());
}
JSValue JSSharedWorker::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSSharedWorkerConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

JSC::JSValue toJS(JSC::ExecState* exec, JSDOMGlobalObject* globalObject, SharedWorker* object)
{
    return getDOMObjectWrapper<JSSharedWorker>(exec, globalObject, object);
}
SharedWorker* toSharedWorker(JSC::JSValue value)
{
    return value.inherits(&JSSharedWorker::s_info) ? static_cast<JSSharedWorker*>(asObject(value))->impl() : 0;
}

}

#endif // ENABLE(SHARED_WORKERS)