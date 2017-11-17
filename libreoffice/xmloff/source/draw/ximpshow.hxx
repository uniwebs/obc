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

#ifndef INCLUDED_XMLOFF_SOURCE_DRAW_XIMPSHOW_HXX
#define INCLUDED_XMLOFF_SOURCE_DRAW_XIMPSHOW_HXX

#include <xmloff/xmlictxt.hxx>
#include "sdxmlimp_impl.hxx"
#include <memory>

class ShowsImpImpl;

// presentations:animations

class SdXMLShowsContext : public SvXMLImportContext
{
    std::unique_ptr<ShowsImpImpl>   mpImpl;

public:

    SdXMLShowsContext( SdXMLImport& rImport,
        sal_uInt16 nPrfx,
        const OUString& rLocalName,
        const css::uno::Reference< css::xml::sax::XAttributeList>& xAttrList);
    virtual ~SdXMLShowsContext() override;

    virtual SvXMLImportContext * CreateChildContext( sal_uInt16 nPrefix, const OUString& rLocalName,
        const css::uno::Reference< css::xml::sax::XAttributeList>& xAttrList ) override;
};

#endif // INCLUDED_XMLOFF_SOURCE_DRAW_XIMPSHOW_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
