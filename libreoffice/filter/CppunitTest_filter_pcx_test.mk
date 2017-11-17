# -*- Mode: makefile-gmake; tab-width: 4; indent-tabs-mode: t -*-
#
# This file is part of the LibreOffice project.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

$(eval $(call gb_CppunitTest_CppunitTest,filter_pcx_test))

$(eval $(call gb_CppunitTest_use_external,filter_pcx_test,boost_headers))

$(eval $(call gb_CppunitTest_add_exception_objects,filter_pcx_test, \
    filter/qa/cppunit/filters-pcx-test \
))

$(eval $(call gb_CppunitTest_use_libraries,filter_pcx_test, \
    gie \
	sal \
	test \
	tl \
	unotest \
	vcl \
))

$(eval $(call gb_CppunitTest_use_sdk_api,filter_pcx_test))

$(eval $(call gb_CppunitTest_use_ure,filter_pcx_test))
$(eval $(call gb_CppunitTest_use_vcl,filter_pcx_test))

$(eval $(call gb_CppunitTest_use_components,filter_pcx_test,\
    configmgr/source/configmgr \
))

$(eval $(call gb_CppunitTest_use_configuration,filter_pcx_test))

# vim: set noet sw=4 ts=4:
