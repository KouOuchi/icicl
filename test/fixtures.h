#include "icicl.h"

#ifdef USE_ICICL
using namespace icicl;
#endif

struct tests_fixture
{
  tests_fixture()
  {
    ICICL_CONFIG_THROW_EXCEPTION(true);
    ICICL_CONFIG_LOG_LEVEL(severity_level::info);
  }

  ~tests_fixture() { }
};

