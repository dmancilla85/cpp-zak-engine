#include "actorMgr.h"

Actor *ActorMgr::_list[MAX_ACTORS];
int ActorMgr::_lastElement = 0;
int ActorMgr::_lastPlayer = 0;

float ActorMgr::_hypnotizedTotalTime = 0;
float ActorMgr::_hypnotizedTime = 0;


bool ActorMgr::Register (Actor *actor) {
	// preguntamos si el arreglo no está lleno
	if (_lastElement < MAX_ACTORS) {

		// Si es un jugador, lo insertamos
		// adelante en el arreglo
		if (strcmp(actor->GetName(), "pacman") == 0) {
			int i=0;
			
			// Llevamos al primer fantasma
			// a la última posición para ocupar
			// su lugar por el jugador
			_list[_lastElement] = _list[_lastPlayer];
			_list[_lastPlayer] = actor;
			_lastElement++;
			_lastPlayer++;
			return true;

		} else {

			//Lo insertamos en la última posición
			_list[_lastElement] = actor;
			_lastElement++;
			return true;
		}
	}

	return false;
}

bool ActorMgr::Unregister (Actor *actor){
	int i=0;

	while (i < _lastElement && _list[i] != actor) {
		i++;
	}

	if (_list[i] == actor) {

		if (i < _lastPlayer) {
			_lastPlayer--;
			_lastElement--;

			_list[i] = _list[_lastPlayer];
			_list[_lastPlayer] = _list[_lastElement];

			_list[_lastElement] = NULL;

			return true;

		} else {
			_lastElement--;
			_list[i] = _list[_lastElement];
			_list[_lastElement] = NULL;

			return true;
		}
	}

	return false;
}

void ActorMgr::SendEvent(int event, Actor *sender) {
	if (event == ACTOR_EVENT_PILL) {
		_hypnotizedTime = 0.0f;
	}

	for (int i=0; i<_lastElement; i++) {
		if (_list[i] != sender) {
			_list[i]->SetEvent(event);
		}
	}
}

void ActorMgr::Draw() {
	for (int i=0; i<_lastElement; i++) {
		_list[i]->Draw();
	}
}

void ActorMgr::Update(float dt) {
	static int tile;

	if (_hypnotizedTime < _hypnotizedTotalTime)
		_hypnotizedTime += dt;

	for (int i=0; i<_lastElement; i++) {
		_list[i]->Update(dt);

		if (i < _lastPlayer) {
			for (int j=_lastPlayer; j < _lastElement; j++) {

				if (_list[j]->GetState() == GHOST_STATE_SEARCH) {
					if (_list[j]->IsInRange(_list[i])){ 
						_list[j]->SetEvent(ACTOR_EVENT_FOUND);
						_list[j]->SetPlayer(_list[i]);
					} 
				} else if (_list[j]->GetState() == GHOST_STATE_CHASE) {
					if (!_list[j]->IsInRange(_list[j]->GetPlayer())) {
						_list[j]->SetPlayer(NULL);
						_list[j]->SetEvent(ACTOR_EVENT_LOST);
					}
				}
			}

		} else {
			if (_list[i]->GetState() == GHOST_STATE_HYPNOTIZED) {
				if (_hypnotizedTime >= _hypnotizedTotalTime) {
					_list[i]->SetEvent(ACTOR_EVENT_TIME);
				}
			} 
		}		
	}
}
