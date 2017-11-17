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

#include <config_options.h>

#include <sfx2/msg.hxx>
#include <svl/stritem.hxx>
#include <svl/eitem.hxx>
#include <sfx2/zoomitem.hxx>
#include <svx/zoomslideritem.hxx>
#include <svx/svxids.hrc>
#include <svl/slstitm.hxx>

#ifdef DISABLE_DYNLOADING
/* Avoid clash with the ones from svx/source/form/typemap.cxx */
#define aSfxInt16Item_Impl starmath_source_appl_typemap_aSfxInt16Item_Impl
#endif

#define SFX_TYPEMAP
#include "smslots.hxx"

#ifdef DISABLE_DYNLOADING
#undef aSfxInt16Item_Impl
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
