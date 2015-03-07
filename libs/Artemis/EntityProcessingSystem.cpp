#include "Artemis/EntityProcessingSystem.h"

namespace artemis {
	
	bool EntityProcessingSystem::checkProcessing() {
		return true;
	}

	void EntityProcessingSystem::processEntities(ImmutableBag<Entity*>& bag) {
		for(int i=0; i < bag.getCount(); i++) 
			{processEntity(*bag.get(i));}
	}

  void EntityProcessingSystem::renderEntities(ImmutableBag<Entity*>& bag) 
  {
    for(int i=0; i < bag.getCount(); i++) 
    {
      renderEntity( *bag.get(i) );
    }
  }

};
