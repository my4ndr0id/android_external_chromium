// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/http/url_security_manager.h"

#include "base/basictypes.h"
#include "googleurl/src/gurl.h"
#include "net/base/net_errors.h"
#include "net/http/http_auth_filter.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace net {

namespace {

struct TestData {
  const char* url;
  bool succeds_in_windows_default;
  bool succeeds_in_whitelist;
};

const char* kTestAuthWhitelist = "*example.com,*foobar.com,baz";

// Under Windows the following will be allowed by default:
//    localhost
//    host names without a period.
// In Posix systems (or on Windows if a whitelist is specified explicitly),
// everything depends on the whitelist.
const TestData kTestDataList[] = {
  { "http://localhost", true, false },
  { "http://bat", true, false },
  { "http://www.example.com", false, true },
  { "http://example.com", false, true },
  { "http://foobar.com", false, true },
  { "http://boo.foobar.com", false, true },
  { "http://baz", true, true },
  { "http://www.exampl.com", false, false },
  { "http://example.org", false, false },
  { "http://foobar.net", false, false },
  { "http://boo.fubar.com", false, false },
};

}  // namespace

// For Windows, This relies on the contents of the registry, so in theory it
// might fail.
TEST(URLSecurityManager, FLAKY_CreateNoWhitelist) {
  scoped_ptr<URLSecurityManager> url_security_manager(
      URLSecurityManager::Create(NULL));
  ASSERT_TRUE(url_security_manager.get());

  for (size_t i = 0; i < arraysize(kTestDataList); ++i) {
    GURL gurl(kTestDataList[i].url);
    bool can_use_default =
        url_security_manager->CanUseDefaultCredentials(gurl);

#if defined(OS_WIN)
    EXPECT_EQ(kTestDataList[i].succeds_in_windows_default, can_use_default)
        << " Run: " << i << " URL: '" << gurl << "'";
#else
    // No whitelist means nothing can use the default.
    EXPECT_FALSE(can_use_default)
        << " Run: " << i << " URL: '" << gurl << "'";
#endif // OS_WIN
  }
}

TEST(URLSecurityManager, CreateWhitelist) {
  HttpAuthFilterWhitelist* auth_filter = new HttpAuthFilterWhitelist();
  ASSERT_TRUE(auth_filter);
  auth_filter->SetWhitelist(kTestAuthWhitelist);
  // The URL security manager takes ownership of |auth_filter|.
  scoped_ptr<URLSecurityManager> url_security_manager(
      URLSecurityManager::Create(auth_filter));
  ASSERT_TRUE(url_security_manager.get());

  for (size_t i = 0; i < arraysize(kTestDataList); ++i) {
    GURL gurl(kTestDataList[i].url);
    bool can_use_default =
        url_security_manager->CanUseDefaultCredentials(gurl);

    EXPECT_EQ(kTestDataList[i].succeeds_in_whitelist, can_use_default)
        << " Run: " << i << " URL: '" << gurl << "'";
  }
}

}  // namespace net