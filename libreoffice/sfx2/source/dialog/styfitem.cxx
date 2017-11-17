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

#include <sfx2/styfitem.hxx>
#include <tools/rcid.h>

SfxStyleFamilyItem::SfxStyleFamilyItem(SfxStyleFamily nFamily_, const OUString &rName, const Image& rImage, const ResId &rStringArrayId)
    : nFamily(nFamily_)
    , aText(rName)
    , aImage(rImage)
{
    ResStringArray aResList(rStringArrayId);
    aFilterList.resize(aResList.Count());
    for (sal_uInt32 i = 0; i < aResList.Count(); ++i)
    {
        aFilterList[i].aName = aResList.GetString(i);
        aFilterList[i].nFlags = aResList.GetValue(i);
    }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
