#include "subject.h"
#include "observer.h"

void Subject::attach(Observer *o)
{
  observers.emplace_back(o);
}

void Subject::detach(Observer *o)
{
  for (auto it = observers.begin(); it != observers.end(); ++it)
  {
    if (*it == o)
    {
      observers.erase(it);
      break;
    }
  }
}

void Subject::clear() {
  for (auto ob : observers)
  {
    ob->clear();
  }
}

void Subject::notifyObservers(bool over)
{
  for (auto ob : observers)
  {
    ob->notify(over);
  }
}

void Subject::notifyObserversPrompt()
{
  for (auto ob : observers)
  {
    ob->prompt();
  }
}

