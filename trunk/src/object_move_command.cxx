//  $Id$
//
//  Flexlay - A Generic 2D Game Editor
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include "object_layer.hxx"
#include "objmap_object.hxx"
#include "object_move_command.hxx"

class ObjectMoveCommandImpl : public CommandImpl
{
public:
  ObjectMoveCommandImpl() {}
  virtual ~ObjectMoveCommandImpl() {}

  ObjectLayer objmap;
  
  struct Obj {
    CL_Point old_pos;
    CL_Point new_pos;
    int id;
  };
  
  typedef std::vector<Obj> Objects;
  Objects objects;

  void execute();
  void redo();
  void undo();

  std::string serialize();
};

ObjectMoveCommand::ObjectMoveCommand(const ObjectLayer& o)
  : impl(new ObjectMoveCommandImpl())
{
  impl->objmap = o;
}

ObjectMoveCommand::~ObjectMoveCommand()
{
}
  
void
ObjectMoveCommandImpl::execute()
{
  for(ObjectMoveCommandImpl::Objects::iterator i = objects.begin(); 
      i != objects.end();
      ++i)
    {
      ObjMapObject* obj = objmap.get_object(i->id);
      if (obj) 
        {
          i->new_pos = obj->get_pos();
        }
    }
}

void
ObjectMoveCommand::add_obj(int id)
{
  ObjMapObject* obj = impl->objmap.get_object(id);

  if (obj)
    {
      ObjectMoveCommandImpl::Obj o;
      o.id      = id;
      o.old_pos = obj->get_pos();
      impl->objects.push_back(o);
    }
}

void
ObjectMoveCommandImpl::redo()
{
  for(ObjectMoveCommandImpl::Objects::iterator i = objects.begin(); 
      i != objects.end();
      ++i)
    {
      ObjMapObject* obj = objmap.get_object(i->id);
      if (obj)
        {
          obj->set_pos(i->new_pos);
        }
    }  
}

void
ObjectMoveCommandImpl::undo()
{
  for(ObjectMoveCommandImpl::Objects::iterator i = objects.begin(); 
      i != objects.end();
      ++i)
    {
      ObjMapObject* obj = objmap.get_object(i->id);
      if (obj)
        {
          obj->set_pos(i->old_pos);
        }
    }
}

std::string
ObjectMoveCommandImpl::serialize()
{
  return "";
}

Command
ObjectMoveCommand::to_command()
{
  return Command(impl);
}

/* EOF */
