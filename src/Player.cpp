/* Copyright (C) 2011 Rainmeter Project Developers
 *
 * This Source Code Form is subject to the terms of the GNU General Public
 * License; either version 2 of the License, or (at your option) any later
 * version. If a copy of the GPL was not distributed with this file, You can
 * obtain one at <https://www.gnu.org/licenses/gpl-2.0.html>. */

#include "Player.h"

/*
** Constructor.
**
*/
Player::Player()
    : m_Initialized(false), m_TrackCount(), m_State(), m_Number(), m_Year(),
      m_Shuffle(false), m_Repeat(false), m_Duration(), m_Position(), m_Rating(),
      m_Volume(), m_getCover(false) {
  // Get temporary file for cover art
  WCHAR buffer[MAX_PATH];
  GetTempPath(MAX_PATH, buffer);
  GetTempFileName(buffer, L"jpg", 0, buffer);
  m_TempCoverPath = buffer;
}

/*
** Destructor.
**
*/
Player::~Player() { DeleteFile(m_TempCoverPath.c_str()); }

/*
** Called during update of main measure.
**
*/
void Player::UpdateMeasure() { UpdateData(); }

/*
** Default implementation for getting cover.
**
*/
void Player::FindCover() {
  TagLib::FileRef fr(m_FilePath.c_str(), false);
  if (!fr.isNull() && CCover::GetEmbedded(fr, m_TempCoverPath)) {
    m_CoverPath = m_TempCoverPath;
  } else {
    std::wstring trackFolder = CCover::GetFileFolder(m_FilePath);

    if (!CCover::GetLocal(L"cover", trackFolder, m_CoverPath) &&
        !CCover::GetLocal(L"folder", trackFolder, m_CoverPath)) {
      // Nothing found
      m_CoverPath.clear();
    }
  }
}

/*
** Clear track information.
**
*/
void Player::ClearData(bool all) {
  m_State = STATE_STOPPED;
  m_Artist.clear();
  m_Album.clear();
  m_Title.clear();
  m_Genre.clear();
  m_FilePath.clear();
  m_CoverPath.clear();
  m_Duration = 0;
  m_Position = 0;
  m_Rating = 0;
  m_Number = 0;
  m_Year = 0;

  if (all) {
    m_Volume = 0;
    m_Shuffle = false;
    m_Repeat = false;
  }
}
