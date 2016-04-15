
/*
                       ___                            __
                      /\_ \                          /\ \__
                   __ \//\ \     ___     ___     ____\ \  _\
                 /'_ `\ \ \ \   / __`\  / __`\  /  __\\ \ \/
                /\ \ \ \ \_\ \_/\ \ \ \/\ \ \ \/\__   \\ \ \_
                \ \____ \/\____\ \____/\ \____/\/\____/ \ \__\
                 \/___/\ \/____/\/___/  \/___/  \/___/   \/__/
                   /\____/
                   \_/__/

                   OpenGL framework for fast demo programming

                             http://www.gloost.org

    This file is part of the gloost framework. You can use it in parts or as
       whole under the terms of the GPL (http://www.gnu.org/licenses/#GPL).
*/

// gloost system includes
#include <gloost/human_input/MouseState.h>

// cpp includes
#include <string>
#include <iostream>


namespace gloost
{
namespace human_input
{

/**
  \class   MouseState

  \brief   stores the state of the mouse

  \author  Felix Weiszig
  \date    November 2005
  \remarks ...
*/

////////////////////////////////////////////////////////////////////////////////

/**
  \brief   creates a BinaryBundle instance
  \param   ...
  \remarks ...
*/

/*static*/
MouseState::shared_ptr
MouseState::create()
{
	return shared_ptr(new MouseState());
}

////////////////////////////////////////////////////////////////////////////////

/**
  \brief   creates a BinaryBundle instance
  \param   ...
  \remarks ...
*/

/*static*/
MouseState::shared_ptr
MouseState::create(shared_ptr mouseState)
{
	auto instance =  shared_ptr(new MouseState());
	instance->_position             = mouseState->_position;
	instance->_oldPosition     = mouseState->_oldPosition;
	instance->_speed           = mouseState->_speed;
	instance->_buttonStates    = mouseState->_buttonStates;
	instance->_lastDownPos     = mouseState->_lastDownPos;
	instance->_lastUpPos       = mouseState->_lastUpPos;
	instance->_mouseDownEvents = mouseState->_mouseDownEvents;
	instance->_mouseUpEvents   = mouseState->_mouseUpEvents;
	return instance;
}

///////////////////////////////////////////////////////////////////////////////

  /// class constructor

MouseState::MouseState():
    _position(),
    _oldPosition(),
    _speed(),
    _buttonStates(),
    _lastDownPos(),
    _lastUpPos(),
    _mouseDownEvents(),
    _mouseUpEvents()
{
	for(unsigned int i=0; i != 6; ++i)
	{
	  _buttonStates[i]    = false;
	  _mouseDownEvents[i] = false;
	  _mouseUpEvents[i]   = false;
	}
}

///////////////////////////////////////////////////////////////////////////////

  /// class constructor

MouseState::~MouseState()
{
	// insert your code here
}

///////////////////////////////////////////////////////////////////////////////

  /// get the location of the mouse

const Point3&
MouseState::getPosition() const
{
  return _position;
}

///////////////////////////////////////////////////////////////////////////////

  /// get the location of the mouse

Point3&
MouseState::getPosition()
{
  return _position;
}

///////////////////////////////////////////////////////////////////////////////

void
MouseState::setPosition(const Point3& loc)
{
  _oldPosition = _position;
  _position    = loc;
  _speed +=  _position - _oldPosition;
}

///////////////////////////////////////////////////////////////////////////////

void
MouseState::setPosition(float x, float y, float z)
{
  _oldPosition = _position;
  _position    = Point3(x,y,z);
  _speed += _position - _oldPosition;
}


///////////////////////////////////////////////////////////////////////////////

  /// get the location of the mouse one frame before

const Point3&
MouseState::getOldPosition() const
{
  return _oldPosition;
}

///////////////////////////////////////////////////////////////////////////////

  /// get the moving speed of the mouse (in pixel/frame)

const Vector3&
MouseState::getSpeed() const
{
  return _speed;
}

///////////////////////////////////////////////////////////////////////////////

  /// get the moving speed of the mouse (in pixel/frame)

Vector3&
MouseState::getSpeed()
{
  return _speed;
}

///////////////////////////////////////////////////////////////////////////////

  /// get the coordinates of the last mouseUp

const Point3&
MouseState::getLastMouseDownPosition() const
{
  return _lastDownPos;
}

///////////////////////////////////////////////////////////////////////////////

  /// get the coordinates of the last mouseUp

const Point3&
MouseState::getLastMouseUpPosition() const
{
  return _lastUpPos;
}

///////////////////////////////////////////////////////////////////////////////

  /// set the speed of the mouse to zero

void
MouseState::setSpeedToZero()
{
  _speed = {0.0,0.0,0.0};
}

///////////////////////////////////////////////////////////////////////////////

  /// reset mouse events so they can be set in the next frame

void
MouseState::resetMouseEvents()
{
  // since the mousewheel will create a button down AND a button up each time
  // I don't handle the up event and do the reset here
  _buttonStates[GLOOST_MOUSESTATE_WHEELUP]   = false;
  _buttonStates[GLOOST_MOUSESTATE_WHEELDOWN] = false;
  for(unsigned int i=0; i!=_mouseDownEvents.size(); ++i)
  {
    _mouseDownEvents[i] = false;
  }

  for(unsigned int i=0; i!=_mouseUpEvents.size(); ++i)
  {
    _mouseUpEvents[i] = false;
  }
}

///////////////////////////////////////////////////////////////////////////////

  /// get the state of one of the mouse bottons

bool
MouseState::getButtonState(unsigned int buttonNum) const
{
  if (buttonNum < 7u)
  {
    return _buttonStates.find(buttonNum)->second;
  }
  return false;
}

///////////////////////////////////////////////////////////////////////////////

  /// get the state of one of the mouse bottons

void
MouseState::setButtonState(unsigned int buttonNum, bool state)
{
  // set mouseUp or mouseDown event
  if (_buttonStates[buttonNum] != state)
  {
    if (state == true)
    {
      setButtonDownEvent(buttonNum, true);
      _lastDownPos = _position;
    }
    else
    {
      setButtonUpEvent(buttonNum, true);
      _lastUpPos = _position;
    }
  }
  _buttonStates[buttonNum] = state;
}

///////////////////////////////////////////////////////////////////////////////

  ///

bool
MouseState::getButtonDownEvent(unsigned int buttonNum) const
{
  if (buttonNum < 6)
  {
    return _mouseDownEvents.find(buttonNum)->second;
  }
  return 0;
}

///////////////////////////////////////////////////////////////////////////////

  ///

void
MouseState::setButtonDownEvent(unsigned int buttonNum, bool state)
{
  if (buttonNum < 6)
  {
    _mouseDownEvents[buttonNum] = state;
  }
}

///////////////////////////////////////////////////////////////////////////////

  ///

bool
MouseState::getButtonUpEvent(unsigned int buttonNum) const
{
  if (buttonNum < 6)
  {
    return _mouseUpEvents.find(buttonNum)->second;
  }

  return 0;
}

///////////////////////////////////////////////////////////////////////////////

  ///

void
MouseState::setButtonUpEvent(unsigned int buttonNum, bool state)
{
  if (buttonNum < 6)
  {
    _mouseUpEvents[buttonNum] = state;
  }
}

///////////////////////////////////////////////////////////////////////////////

  /// transforms the mouse position and speed

void
MouseState::transform(const gloost::Matrix& transformation)
{
  _position         = transformation * _position;
  _oldPosition = transformation * _oldPosition;
  _speed       = transformation * _speed;
  _lastDownPos = transformation * _lastDownPos;
  _lastUpPos   = transformation * _lastUpPos;
}

///////////////////////////////////////////////////////////////////////////////

} // namespace human_input
} // namespace gloost


