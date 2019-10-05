#include "icicl.h"

#include <list>
#include <exception>
#include <iostream>
#include <mutex>

namespace icicl
{
using namespace std;

namespace internal
{
static bool throw_exception_ = true;
static map<string, tuple<long, long> > instance_map_;

mutex mutex_;

void _constructor(const type_info& _x)
{
  string t_name(_x.name());
  lock_guard<mutex> lock_gurard(mutex_);

  map<string, tuple<long, long> >::iterator it = instance_map_.find(t_name);
  if (it != instance_map_.end())
  {
    it->second = make_tuple(get<0>(it->second) + 1,
                            get<1>(it->second) + 1);
  }
  else
  {
    instance_map_.insert(pair<string, tuple<long, long> >
                         (t_name, make_tuple(1, 1)));
  }
}

void _destructor(const type_info& _x)
{
  string t_name(_x.name());
  lock_guard<mutex> lock_gurard(mutex_);

  map<string, tuple<long, long> >::iterator it = instance_map_.find(t_name);
  if (it != instance_map_.end())
  {
    it->second = make_tuple(get<0>(it->second) - 1, get<1>(it->second));
  }
  else
  {
    instance_map_.insert(pair<string, tuple<long, long> >
                         (t_name, make_tuple(-1, 0)));
  }
}

void _count()
{
  lock_guard<mutex> lock_gurard(mutex_);

  for (map<string, tuple<long, long> >::iterator it = instance_map_.begin();
       it != instance_map_.end(); ++it)
  {
    cerr << it->first << ": accum=" <<
         get<0>(it->second) << ": total=" << get<1>(it->second) << endl;
  }
}

void _check()
{
  bool found = false;
  lock_guard<mutex> lock_gurard(mutex_);

  for (map<string, tuple<long, long> >::iterator it = instance_map_.begin();
       it != instance_map_.end(); ++it)
  {
    if (get<0>(it->second) != 0)
    {
      cerr << it->first << ": accum=" <<
           get<0>(it->second) << ": total=" << get<1>(it->second) << endl;
      found = true;
    }
  }

  if (found)
  {
    string message("detect memory leak!");
    cerr << message;

    if (throw_exception_)
    {
      throw std::exception();
    }
  }
}

void _initialize()
{
  lock_guard<mutex> lock_gurard(mutex_);

  instance_map_.clear();
}

// throw or no throw when you call check()
void _config_throw_exception(bool _x)
{
  throw_exception_ = _x;
}

int _get_accum(const std::type_info& _x)
{
  string t_name(_x.name());
  lock_guard<mutex> lock_gurard(mutex_);

  map<string, tuple<long, long> >::iterator it = instance_map_.find(t_name);
  if (it == instance_map_.end())
  {
    return 0;
  }
  else
  {
    return get<0>(it->second);
  }
}

int _get_total(const std::type_info& _x)
{
  string t_name(_x.name());
  lock_guard<mutex> lock_gurard(mutex_);

  map<string, tuple<long, long> >::iterator it = instance_map_.find(t_name);
  if (it == instance_map_.end())
  {
    return 0;
  }
  else
  {
    return get<1>(it->second);
  }
}
} // namespace icicl::internal

void constructor(const std::type_info& _x)
{
  internal::_constructor(_x);
}
void destructor(const std::type_info& _x)
{
  internal::_destructor(_x);
}
void initialize()
{
  internal::_initialize();
}
void count()
{
  internal::_count();
}
int get_accum(const std::type_info& _x)
{
  return internal::_get_accum(_x);
}
int get_total(const std::type_info& _x)
{
  return internal::_get_total(_x);
}
void check()
{
  internal::_check();
}
void config_throw_exception(bool _x)
{
  internal::_config_throw_exception(_x);
}

} // namespace icicl
