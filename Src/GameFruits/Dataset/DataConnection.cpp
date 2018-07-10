#include "DataConnection.h"

using namespace GAME_FRUITS;

Game DataConnection::m_game;

Scene* DataConnection::m_currScene = m_game.m_scenes[0];

Object* DataConnection::m_currObject = NULL;

wxWindow* DataConnection::m_stage = NULL;

VIEW::BACKSTAGE::DstPanel* DataConnection::m_dstPanel = NULL;

wxNotebook* DataConnection::m_libraryNotebook = NULL;