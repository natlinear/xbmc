/*
 *      Copyright (C) 2005-2013 Team XBMC
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

#include "settings/lib/ISettingCallback.h"
#include "settings/lib/ISettingsHandler.h"
#include <string>
#include <vector>
#include <map>

class CSetting;

class CLinuxTimezone : public ISettingCallback, public ISettingsHandler
{
public:
   CLinuxTimezone();

   void OnSettingChanged(std::shared_ptr<const CSetting> setting) override;

   void OnSettingsLoaded() override;

   std::string GetOSConfiguredTimezone();

   std::vector<std::string> GetCounties();
   std::vector<std::string> GetTimezonesByCountry(const std::string& country);
   std::string GetCountryByTimezone(const std::string& timezone);

   void SetTimezone(std::string timezone);
   int m_IsDST = 0;

   static void SettingOptionsTimezoneCountriesFiller(std::shared_ptr<const CSetting> setting, std::vector< std::pair<std::string, std::string> > &list, std::string &current, void *data);
   static void SettingOptionsTimezonesFiller(std::shared_ptr<const CSetting> setting, std::vector< std::pair<std::string, std::string> > &list, std::string &current, void *data);

private:
   std::vector<std::string> m_counties;
   std::map<std::string, std::string> m_countryByCode;
   std::map<std::string, std::string> m_countryByName;

   std::map<std::string, std::vector<std::string> > m_timezonesByCountryCode;
   std::map<std::string, std::string> m_countriesByTimezoneName;
};

extern CLinuxTimezone g_timezone;

