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

#include "gtest/gtest.h"

#include "threads/Thread.h"

#define MILLIS(x) x

inline static void SleepMillis(unsigned int millis) { XbmcThreads::ThreadSleep(millis); }

template<class E> inline static bool waitForWaiters(E& event, int numWaiters, int milliseconds)
{
  for( int i = 0; i < milliseconds; i++)
  {
    if (event.getNumWaits() == numWaiters)
      return true;
    SleepMillis(1);
  }
  return false;
}

inline static bool waitForThread(std::atomic<long>& mutex, int numWaiters, int milliseconds)
{
  CCriticalSection sec;
  for( int i = 0; i < milliseconds; i++)
  {
    if (mutex == (long)numWaiters)
      return true;

    {
      CSingleLock tmplock(sec); // kick any memory syncs
    }
    SleepMillis(1);
  }
  return false;
}

class AtomicGuard
{
  std::atomic<long>* val;
public:
  inline AtomicGuard(std::atomic<long>* val_) : val(val_) { if (val) ++(*val); }
  inline ~AtomicGuard() { if (val) --(*val); }
};

class thread
{
  IRunnable* f;
  CThread* cthread;

//  inline thread(const thread& other) { }
public:
  inline explicit thread(IRunnable& runnable) :
    f(&runnable), cthread(new CThread(f, "DumbThread"))
  {
    cthread->Create();
  }

  inline thread() : f(NULL), cthread(NULL) {}
  ~thread()
  {
    delete cthread;
  }

  inline thread(thread& other) : f(other.f), cthread(other.cthread) { other.f = NULL; other.cthread = NULL; }
  inline thread& operator=(thread& other) { f = other.f; other.f = NULL; cthread = other.cthread; other.cthread = NULL; return *this; }

  void join()
  {
    cthread->WaitForThreadExit((unsigned int)-1);
  }

  bool timed_join(unsigned int millis)
  {
    return cthread->WaitForThreadExit(millis);
  }
};

