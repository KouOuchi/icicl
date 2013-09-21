#include "icicl.h"

#include <list>
#include <map>
#include <exception>
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/exception/all.hpp>

namespace icicl
{

using namespace boost;
using namespace boost::log;
using namespace std;

bool throw_exception_ = true;
map<string, tuple<long, long> > instance_map_;

void constructor(const type_info& _x)
{
  string t_name(_x.name());

  BOOST_LOG_TRIVIAL(trace) << t_name << " +1";

  map<string, tuple<long, long> >::iterator it = instance_map_.find(t_name);
  if(it != instance_map_.end())
  {
    it->second = make_tuple(it->second.get<0>() + 1, it->second.get<1>() + 1);
  }
  else
  {
    instance_map_.insert( pair<string, tuple<long, long> >
                          (t_name, make_tuple(1, 1)) );
  }
}

void destructor(const type_info& _x)
{
  string t_name(_x.name());

  BOOST_LOG_TRIVIAL(trace) << t_name << " -1";

  map<string, tuple<long, long> >::iterator it = instance_map_.find(t_name);
  if(it != instance_map_.end())
  {
    it->second = make_tuple(it->second.get<0>() - 1, it->second.get<1>());
  }
  else
  {
    instance_map_.insert( pair<string, tuple<long, long> >
                          (t_name, make_tuple(-1, 0)) );
  }
}
void count()
{
  for(map<string, tuple<long, long> >::iterator it = instance_map_.begin();
      it != instance_map_.end(); ++it)
  {
    BOOST_LOG_TRIVIAL(info) << it->first << ": accum=" <<
                            it->second.get<0>() << ": total=" << it->second.get<1>();
  }
}
void check()
{
  bool found = false;
  for(map<string, tuple<long, long> >::iterator it = instance_map_.begin();
      it != instance_map_.end(); ++it)
  {
    if(it->second.get<0>() != 0)
    {
      BOOST_LOG_TRIVIAL(fatal) << it->first << ": accum=" <<
                               it->second.get<0>() << ": total=" << it->second.get<1>();
      found = true;
    }
  }

  if(found)
  {
    string message("detect memory leak!");
    BOOST_LOG_TRIVIAL(fatal) << message;

    if(throw_exception_)
    { BOOST_THROW_EXCEPTION(std::exception()); }
  }
}
void initialize()
{
  instance_map_.clear();
}

// filter logging
void config_log_level(severity_level_enum _x)
{
  using namespace boost::log;

  if(severity_level::trace == _x)
  { core::get()->set_filter( trivial::severity >= trivial::trace); }
  else if(severity_level::debug == _x)
  { core::get()->set_filter( trivial::severity >= trivial::debug); }
  else if(severity_level::info == _x)
  { core::get()->set_filter( trivial::severity >= trivial::info); }
  else if(severity_level::warning == _x)
  { core::get()->set_filter( trivial::severity >= trivial::warning); }
  else if(severity_level::error == _x)
  { core::get()->set_filter( trivial::severity >= trivial::error); }
  else if(severity_level::fatal == _x)
  { core::get()->set_filter( trivial::severity >= trivial::fatal); }

}

// throw or no throw when you call check()
void config_throw_exception(bool _x)
{
  throw_exception_ = _x;
}

int get_accum(const std::type_info& _x)
{
  string t_name(_x.name());
  map<string, tuple<long, long> >::iterator it = instance_map_.find(t_name);
  if(it == instance_map_.end())
  { return 0; }
  else
  { return it->second.get<0>(); }
}

int get_total(const std::type_info& _x)
{
  string t_name(_x.name());
  map<string, tuple<long, long> >::iterator it = instance_map_.find(t_name);
  if(it == instance_map_.end())
  { return 0; }
  else
  { return it->second.get<1>(); }
}



}
// namespace icicl
