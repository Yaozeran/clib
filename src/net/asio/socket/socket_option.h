#pragma once


namespace socket_option
{  

template<int Level, int Name>
class boolean
{
public:

  boolean() : value_(0) {}

  operator bool() const { return !!value_; }

  bool operator!() const { return !value_; }

  template<typename Protocol>
  int level(const Protocol&) const { return Level; }

  template<typename Protocol>
  int name(const Protocol&) const { return Name; }

private:

  int value_;

};

} // namespace socket_option