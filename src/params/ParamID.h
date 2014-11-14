#pragma once

class ParamID
{

  public:

  static string make( string entity_id, string component_id, string data_id )
  {
    return entity_id + sep() + component_id + sep() + data_id;
  };

  private:

  static const string& sep()
  {
    static string _sep = "__";
    return _sep;
  };

};

