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
#ifndef INCLUDED_SW_SOURCE_UIBASE_INC_GRFSH_HXX
#define INCLUDED_SW_SOURCE_UIBASE_INC_GRFSH_HXX

#include <memory>
#include "frmsh.hxx"

class SwGrfShell: public SwBaseShell
{
    class SwExternalToolEdit;
    std::vector<std::unique_ptr<SwExternalToolEdit>> m_ExternalEdits;

public:
    SFX_DECL_INTERFACE(SW_GRFSHELL)

private:
    /// SfxInterface initializer.
    static void InitInterface_Impl();

public:
    void Execute(SfxRequest& rRequest);
    void ExecAttr(SfxRequest& rRequest);
    void GetAttrState(SfxItemSet& rRequest);

    void ExecuteRotation(SfxRequest &rRequest);
    void GetAttrStateForRotation(SfxItemSet& rRequest);

    SwGrfShell(SwView &rView);
    virtual ~SwGrfShell() override;
};

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
