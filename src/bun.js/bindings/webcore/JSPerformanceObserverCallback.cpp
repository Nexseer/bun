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
#include "JSPerformanceObserverCallback.h"

#include "JSDOMConvertBase.h"
#include "JSDOMConvertInterface.h"
#include "JSDOMExceptionHandling.h"
#include "JSDOMGlobalObject.h"
#include "JSPerformanceObserver.h"
#include "JSPerformanceObserverEntryList.h"
#include "ScriptExecutionContext.h"
#include "ZigGlobalObject.h"

namespace WebCore {
using namespace JSC;

JSPerformanceObserverCallback::JSPerformanceObserverCallback(JSObject* callback, JSDOMGlobalObject* globalObject)
    : PerformanceObserverCallback(globalObject->scriptExecutionContext())
    , m_data(new JSCallbackDataWeak(globalObject->vm(), callback, this))
{
}

JSPerformanceObserverCallback::~JSPerformanceObserverCallback()
{
    ScriptExecutionContext* context = scriptExecutionContext();
    // When the context is destroyed, all tasks with a reference to a callback
    // should be deleted. So if the context is 0, we are on the context thread.
    if (!context || context->isContextThread())
        delete m_data;
    else
        RELEASE_ASSERT_NOT_REACHED();
#ifndef NDEBUG
    m_data = nullptr;
#endif
}

CallbackResult<typename IDLUndefined::ImplementationType> JSPerformanceObserverCallback::handleEvent(typename IDLInterface<PerformanceObserver>::ParameterType thisObject, typename IDLInterface<PerformanceObserverEntryList>::ParameterType entries, typename IDLInterface<PerformanceObserver>::ParameterType observer)
{
    if (!canInvokeCallback())
        return CallbackResultType::UnableToExecute;

    Ref<JSPerformanceObserverCallback> protectedThis(*this);

    auto& globalObject = *jsCast<JSDOMGlobalObject*>(m_data->callback()->globalObject());
    auto& vm = globalObject.vm();

    JSLockHolder lock(vm);
    auto& lexicalGlobalObject = globalObject;
    JSValue thisValue = toJS<IDLInterface<PerformanceObserver>>(lexicalGlobalObject, globalObject, thisObject);
    MarkedArgumentBuffer args;
    args.append(toJS<IDLInterface<PerformanceObserverEntryList>>(lexicalGlobalObject, globalObject, entries));
    args.append(&observer == &thisObject ? thisValue : toJS<IDLInterface<PerformanceObserver>>(lexicalGlobalObject, globalObject, observer));
    ASSERT(!args.hasOverflowed());

    NakedPtr<JSC::Exception> returnedException;
    m_data->invokeCallback(vm, thisValue, args, JSCallbackData::CallbackType::Function, Identifier(), returnedException);
    if (returnedException) {
        UNUSED_PARAM(lexicalGlobalObject);
        reportException(m_data->callback()->globalObject(), returnedException);
        return CallbackResultType::ExceptionThrown;
    }

    return {};
}

void JSPerformanceObserverCallback::visitJSFunction(JSC::AbstractSlotVisitor& visitor)
{
    m_data->visitJSFunction(visitor);
}

void JSPerformanceObserverCallback::visitJSFunction(JSC::SlotVisitor& visitor)
{
    m_data->visitJSFunction(visitor);
}

JSC::JSValue toJS(PerformanceObserverCallback& impl)
{
    if (!static_cast<JSPerformanceObserverCallback&>(impl).callbackData())
        return jsNull();

    return static_cast<JSPerformanceObserverCallback&>(impl).callbackData()->callback();
}

} // namespace WebCore