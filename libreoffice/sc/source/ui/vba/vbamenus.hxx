/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef INCLUDED_SC_SOURCE_UI_VBA_VBAMENUS_HXX
#define INCLUDED_SC_SOURCE_UI_VBA_VBAMENUS_HXX

#include <ooo/vba/excel/XMenus.hpp>
#include <ooo/vba/excel/XMenu.hpp>
#include <ooo/vba/XCommandBarControls.hpp>
#include <vbahelper/vbahelperinterface.hxx>
#include <vbahelper/vbacollectionimpl.hxx>

typedef CollTestImplHelper< ov::excel::XMenus > Menus_BASE;

class ScVbaMenus : public Menus_BASE
{
private:
    css::uno::Reference< ov::XCommandBarControls > m_xCommandBarControls;

public:
    /// @throws css::uno::RuntimeException
    ScVbaMenus( const css::uno::Reference< ov::XHelperInterface >& xParent, const css::uno::Reference< css::uno::XComponentContext >& xContext, const css::uno::Reference< ov::XCommandBarControls >& xCommandBarControls );

    // XEnumerationAccess
    virtual css::uno::Type SAL_CALL getElementType() override;
    virtual css::uno::Reference< css::container::XEnumeration > SAL_CALL createEnumeration() override;
    virtual css::uno::Any createCollectionObject( const css::uno::Any& aSource ) override;

    // Methods
    virtual sal_Int32 SAL_CALL getCount() override;
    virtual css::uno::Any SAL_CALL Item( const css::uno::Any& Index, const css::uno::Any& /*Index2*/ ) override;
    virtual css::uno::Reference< ov::excel::XMenu > SAL_CALL Add( const OUString& Caption, const css::uno::Any& Before, const css::uno::Any& Restore ) override;
    // XHelperInterface
    virtual OUString getServiceImplName() override;
    virtual css::uno::Sequence<OUString> getServiceNames() override;
};

#endif // INCLUDED_SC_SOURCE_UI_VBA_VBAMENUS_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
