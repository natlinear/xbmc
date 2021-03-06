/*
 *      Copyright (C) 2014 Team XBMC
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include <set>

#include "addons/Resource.h"
#include "utils/Locale.h"

namespace ADDON
{
class CLanguageResource : public CResource
{
public:
  static std::unique_ptr<CLanguageResource> FromExtension(CAddonInfo addonInfo, const cp_extension_t* ext);

  explicit CLanguageResource(CAddonInfo addonInfo) : CResource(std::move(addonInfo)), m_forceUnicodeFont(false) {};

  CLanguageResource(CAddonInfo addonInfo,
      const CLocale& locale,
      const std::string& charsetGui,
      bool forceUnicodeFont,
      const std::string& charsetSubtitle,
      const std::string& dvdLanguageMenu,
      const std::string& dvdLanguageAudio,
      const std::string& dvdLanguageSubtitle,
      const std::set<std::string>& sortTokens);

  bool IsInUse() const override;

  void OnPostInstall(bool update, bool modal) override;

  bool IsAllowed(const std::string &file) const override;

  const CLocale& GetLocale() const { return m_locale; }

  const std::string& GetGuiCharset() const { return m_charsetGui; }
  bool ForceUnicodeFont() const { return m_forceUnicodeFont; }
  const std::string& GetSubtitleCharset() const { return m_charsetSubtitle; }

  const std::string& GetDvdMenuLanguage() const { return m_dvdLanguageMenu; }
  const std::string& GetDvdAudioLanguage() const { return m_dvdLanguageAudio; }
  const std::string& GetDvdSubtitleLanguage() const { return m_dvdLanguageSubtitle; }

  const std::set<std::string>& GetSortTokens() const { return m_sortTokens; }

  static std::string GetAddonId(const std::string& locale);

  static bool FindLegacyLanguage(const std::string &locale, std::string &legacyLanguage);

private:
  CLocale m_locale;

  std::string m_charsetGui;
  bool m_forceUnicodeFont;
  std::string m_charsetSubtitle;

  std::string m_dvdLanguageMenu;
  std::string m_dvdLanguageAudio;
  std::string m_dvdLanguageSubtitle;

  std::set<std::string> m_sortTokens;
};

}
