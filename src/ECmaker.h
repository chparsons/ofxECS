#pragma once

#include <Artemis/Artemis.h>
#include "ECScomponent.h"
#include "ECSparams.h"
#include "ComponentFactory.h"

class ECmaker
{
  public:

    ECmaker(){};
    ~ECmaker(){};

    void init( artemis::World* world, ComponentFactory* component_factory, Json::Value _entities, int receiver_port )
    {
      this->world = world;
      this->component_factory = component_factory;
      params().init( receiver_port );
      entities_cfg = parse_config( _entities );
    }

    void make_all()
    {
      for ( map< string,Json::Value >::iterator it = entities_cfg.begin(); it != entities_cfg.end(); ++it )
        make_entity( it->first );
    };

    void remove_all()
    {
      for ( map< string,Json::Value >::iterator it = entities_cfg.begin(); it != entities_cfg.end(); ++it )
        remove_entity( it->first );
    };

    artemis::Entity* make_entity( string e_id )
    {
      ofLogNotice("ECmaker") << "\n" << "make_entity by id/tag " << e_id; 

      //si queremos multiples entidades
      //del mismo tipo pasar acá 
      //un e_id que sea uuid
      if ( has_entity( e_id ) )
      {
        artemis::Entity& e = world->getEntityManager()->getEntity( entities_ids[ e_id ] );
        ofLogWarning("ECmaker") << "make_entity by id/tag " << e_id << ": entity already exists (with id: " << e.getId() << ")"; 
        return &e;
      }

      Json::Value comps_cfg = entities_cfg[ e_id ];

      if ( ! comps_cfg.size() )
      {
        ofLogWarning("ECmaker") << "make_entity by id/tag " << e_id << ": components config not found"; 
        return NULL;
      }

      vector<artemis::Component*> components;

      //add config components
      for ( int i = 0; i < comps_cfg.size(); i++ )
      {
        const Json::Value& comp_cfg = comps_cfg[i];
        ECScomponent* comp = component_factory->make( comp_cfg["id"].asString() );
        if ( comp != NULL ) 
        {
          comp->init( e_id, comp_cfg["data"], &(params()) );
          components.push_back( comp );
        }
      }

      if ( ! components.size() )
      {
        ofLogWarning("ECmaker") << "make_entity by id/tag " << e_id << ": components ids not found"; 
        return NULL;
      }

      artemis::Entity& e = world->getEntityManager()->create();
      ofLogNotice("ECmaker") << "\t\t" << "entity " << e_id << " made: entity " << e.getId(); 

      for ( int i = 0; i < components.size(); i++ )
        e.addComponent( components[i] );
      e.refresh();

      world->getTagManager()->subscribe( e_id, e );

      entities_ids[ e_id ] = e.getId();

      return &e;
    }; 

    void remove_entity( string e_id )
    {
      if ( ! has_entity( e_id ) )
      {
        ofLogWarning("ECmaker") << "remove_entity by id/tag " << e_id << ": entity not found"; 
        return;
      }

      artemis::Entity& e = world->getEntityManager()->getEntity( entities_ids[ e_id ] );
      ofLogNotice("ECmaker") << "remove_entity by id/tag " << e_id << ": entity " << e.getId(); 
      world->getEntityManager()->remove( e );

      entities_ids.erase( e_id );
    };

    bool has_entity( string e_id )
    {
      return entities_ids.find( e_id ) != entities_ids.end(); 
    };

  private:

    //a single params receiver!
    static ECSparams& params()
    {
      static ECSparams _params;
      return _params;
    };

    artemis::World* world;
    ComponentFactory* component_factory;
 
    //{ entity_id : [ components ] }
    map<string,Json::Value> entities_cfg;

    //{ tag : id }
    map< string,int > entities_ids; 

    map< string,Json::Value > parse_config( Json::Value _entities )
    {
      map< string,Json::Value > entities_cfg;

      for ( int i = 0; i < _entities.size(); ++i )
      {
        string e_id = _entities[i]["id"].asString();
        entities_cfg[ e_id ] = _entities[i]["components"];
      }

      return entities_cfg;
    };

};

 
