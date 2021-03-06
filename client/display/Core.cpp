//
// Core.cpp for  in /home/lund/Projets/zappy-poney/test
// 
// Made by florian dewulf
// Login   <dewulf_f@epitech.net>
// 
// Started on  Tue Jul 16 09:20:23 2013 florian dewulf
// Last update Tue Jul 16 23:58:53 2013 gery baudry
//

#include	"Core.hpp"

using namespace std;

Core::Core(const string &host, int port, const string &team) : _mem(new Memory), _net(host, port, team), _check(false)
{
}

Core::~Core()
{
  delete this->_mem;
}

void		Core::init()
{
  this->_net.initConnexion();
  this->_mess.init();
  gnl		tmp(this->_net.getSock());

  this->_gnl = tmp;
  while (!this->_net.checkBinary())
    {
      if (this->_net.init(this->_gnl))
	{
	  string tempo = this->_gnl.get_next_line();
	  if (this->_net.initConnexion(tempo))
	    this->_mess.work(tempo, this->_mem);
	}
    }
}

bool		Core::update()
{
  if (this->_mem->pool(this->_event) == false && (this->_event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))))
    {
      this->_mem->close();
      return (false);
    }
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true && this->_check == false)
    {
      this->_mem->checkSouris();
      this->_check = true;
    }
  else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false && this->_check == true)
    this->_check = false;
  if (this->_net.init(this->_gnl))
    return (this->_mess.work(this->_gnl.get_next_line(), this->_mem));
  return (true);
}

void		Core::draw()
{
  this->_mem->clear_win();
  this->_mem->drawCase();
  this->_mem->drawPlayer();
  this->_mem->drawOeuf();
  this->_mem->printText();
  this->_mem->display_win();
}
