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

#ifndef INCLUDED_DBACCESS_SOURCE_UI_INC_ASYNCMODALDIALOG_HXX
#define INCLUDED_DBACCESS_SOURCE_UI_INC_ASYNCMODALDIALOG_HXX

#include <com/sun/star/ui/dialogs/XExecutableDialog.hpp>

namespace dbaui
{

    // AsyncDialogExecutor
    /** helper class for executing (UNO) dialogs modal, but asynchronously
    */
    class AsyncDialogExecutor
    {
    public:
        /** executes the given dialog asynchronously, but still modal

            @throws IllegalArgumentException
                if the given dialog is <NULL/>
            @todo
                allow for a callback for the result
        */
        static void executeModalDialogAsync(
            const css::uno::Reference< css::ui::dialogs::XExecutableDialog >& _rxDialog
        );
    };

} // namespace dbaui

#endif // INCLUDED_DBACCESS_SOURCE_UI_INC_ASYNCMODALDIALOG_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */