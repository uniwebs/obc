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

#ifndef INCLUDED_VCL_GENERIC_GLYPHS_GCACH_FTYP_HXX
#define INCLUDED_VCL_GENERIC_GLYPHS_GCACH_FTYP_HXX

#include "unx/glyphcache.hxx"
#include "PhysicalFontFace.hxx"

// FreetypeFontFile has the responsibility that a font file is only mapped once.
// (#86621#) the old directly ft-managed solution caused it to be mapped
// in up to nTTC*nSizes*nOrientation*nSynthetic times
class FreetypeFontFile
{
public:
    static FreetypeFontFile*      FindFontFile( const OString& rNativeFileName );

    bool                    Map();
    void                    Unmap();

    const unsigned char*    GetBuffer() const { return mpFileMap; }
    int                     GetFileSize() const { return mnFileSize; }
    const OString&          GetFileName() const { return maNativeFileName; }
    int                     GetLangBoost() const { return mnLangBoost; }

private:
    explicit                FreetypeFontFile( const OString& rNativeFileName );

    const OString    maNativeFileName;
    unsigned char*   mpFileMap;
    int                     mnFileSize;
    int                     mnRefCount;
    int                     mnLangBoost;
};

// FreetypeFontInfo corresponds to an unscaled font face
class FreetypeFontInfo
{
public:
                           FreetypeFontInfo( const FontAttributes&,
                               const OString& rNativeFileName,
                               int nFaceNum, sal_IntPtr nFontId);
                          ~FreetypeFontInfo();

    const unsigned char*  GetTable( const char*, sal_uLong* pLength=nullptr ) const;

    FT_FaceRec_*          GetFaceFT();
    void                  ReleaseFaceFT();

    const OString&        GetFontFileName() const   { return mpFontFile->GetFileName(); }
    int                   GetFontFaceIndex() const  { return mnFaceNum; }
    sal_IntPtr            GetFontId() const         { return mnFontId; }
    bool                  IsSymbolFont() const      { return maDevFontAttributes.IsSymbolFont(); }
    const FontAttributes& GetFontAttributes() const { return maDevFontAttributes; }

    void                  AnnounceFont( PhysicalFontCollection* );

    bool                  GetFontCodeRanges( CmapResult& ) const;
    const FontCharMapRef& GetFontCharMap();

private:
    FT_FaceRec_*    maFaceFT;
    FreetypeFontFile*     mpFontFile;
    const int       mnFaceNum;
    int             mnRefCount;
    sal_IntPtr      mnFontId;
    FontAttributes  maDevFontAttributes;

    FontCharMapRef  mxFontCharMap;
};

class FreetypeManager
{
public:
                        FreetypeManager();
                        ~FreetypeManager();

    void                AddFontFile( const OString& rNormalizedName,
                            int nFaceNum, sal_IntPtr nFontId, const FontAttributes&);
    void                AnnounceFonts( PhysicalFontCollection* ) const;
    void                ClearFontList();

    FreetypeFont* CreateFont( const FontSelectPattern& );

private:
    typedef std::unordered_map<sal_IntPtr,FreetypeFontInfo*> FontList;
    FontList            maFontList;

    sal_IntPtr          mnMaxFontId;
};

class FreetypeFontFace : public PhysicalFontFace
{
private:
    FreetypeFontInfo*             mpFreetypeFontInfo;

public:
                            FreetypeFontFace( FreetypeFontInfo*, const FontAttributes& );

    virtual LogicalFontInstance* CreateFontInstance( FontSelectPattern& ) const override;
    virtual PhysicalFontFace* Clone() const override   { return new FreetypeFontFace( *this ); }
    virtual sal_IntPtr      GetFontId() const override { return mpFreetypeFontInfo->GetFontId(); }
};

#endif // INCLUDED_VCL_GENERIC_GLYPHS_GCACH_FTYP_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
