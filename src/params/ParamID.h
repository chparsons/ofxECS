#pragma once

class ParamID
{

  public:

  static string make( string entity_id, string component_id, string data_id )
  {
    return entity_id + sep() + component_id + sep() + data_id;
  };

  static string entity_id( string param_id )
  {
    return ofSplitString( param_id, sep() )[0];
  };

  static string component_id( string param_id )
  {
    return ofSplitString( param_id, sep() )[1];
  };

  static string data_id( string param_id )
  {
    return ofSplitString( param_id, sep() )[2];
  };

  private:

  static const string& sep()
  {
    static string _sep = "__";
    return _sep;
  };

};

