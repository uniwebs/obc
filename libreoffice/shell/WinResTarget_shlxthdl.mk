# -*- Mode: makefile-gmake; tab-width: 4; indent-tabs-mode: t -*-
#
# This file is part of the LibreOffice project.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

$(eval $(call gb_WinResTarget_WinResTarget,shlxthdl))

$(eval $(call gb_WinResTarget_set_include,shlxthdl,\
	$$(INCLUDE) \
	-I$(SRCDIR)/shell/inc \
))

$(eval $(call gb_WinResTarget_use_custom_headers,shlxthdl,\
	shell/source/win32/shlxthandler/res \
))

$(eval $(call gb_WinResTarget_set_rcfile,shlxthdl,shell/source/win32/shlxthandler/res/shlxthdl))

# vim: set shiftwidth=4 tabstop=4 noexpandtab:
