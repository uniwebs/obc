/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */


#include <config_vclplug.h>
#include "KDriver.hxx"
#include <cppuhelper/factory.hxx>

#if ENABLE_TDE

#define kab_component_getFactory tdeab_component_getFactory

#endif // ENABLE_TDE

using namespace connectivity::kab;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::Sequence;
using ::com::sun::star::lang::XSingleServiceFactory;
using ::com::sun::star::lang::XMultiServiceFactory;

typedef Reference< XSingleServiceFactory > (SAL_CALL *createFactoryFunc)
        (
            const Reference< XMultiServiceFactory > & rServiceManager,
            const OUString & rComponentName,
            ::cppu::ComponentInstantiation pCreateFunction,
            const Sequence< OUString > & rServiceNames,
            rtl_ModuleCount*
        );


struct ProviderRequest
{
    Reference< XSingleServiceFactory > xRet;
    Reference< XMultiServiceFactory > const xServiceManager;
    OUString const sImplementationName;

    ProviderRequest(
        void* pServiceManager,
        sal_Char const* pImplementationName
    )
    : xServiceManager(static_cast<XMultiServiceFactory*>(pServiceManager))
    , sImplementationName(OUString::createFromAscii(pImplementationName))
    {
    }

    bool CREATE_PROVIDER(
                const OUString& Implname,
                const Sequence< OUString > & Services,
                ::cppu::ComponentInstantiation Factory,
                createFactoryFunc creator
            )
    {
        if (!xRet.is() && (Implname == sImplementationName))
        {
            try
            {
                xRet = creator( xServiceManager, sImplementationName,Factory, Services, nullptr);
            }
            catch(...)
            {
            }
        }
        return xRet.is();
    }

    void* getProvider() const { return xRet.get(); }
};


extern "C" SAL_DLLPUBLIC_EXPORT void* SAL_CALL kab_component_getFactory(
                    const sal_Char* pImplementationName,
                    void* pServiceManager,
                    void*)
{
    void* pRet = nullptr;
    if (pServiceManager)
    {
        ProviderRequest aReq(pServiceManager,pImplementationName);

        aReq.CREATE_PROVIDER(
            KabDriver::getImplementationName_Static(),
            KabDriver::getSupportedServiceNames_Static(),
            &KabDriver::Create,
            ::cppu::createSingleFactory)
        ;

        if (aReq.xRet.is())
            aReq.xRet->acquire();

        pRet = aReq.getProvider();
    }

    return pRet;
};


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
