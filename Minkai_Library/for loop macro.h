#ifndef FOR_LOOP_MACRO_H
#define FOR_LOOP_MACRO_H

#define FOR_LOOP( x ) for(int index = 0; index < ( x ).size() ; index++)
#define FOR_LOOP_COUNT( x ) for(int count = 1; count <= static_cast<int>( ( x ).size() ); count++)
#define FOR_LOOP_LIST2( x ) for( iter = ( x ).begin(); iter != ( x ).end(); iter++ )
#define FOR_LOOP_LIST( t, x ) for( list< t >::iterator iter = ( x ).begin(); iter != ( x ).end(); iter++ )
#define FOR_LOOP_CONST_LIST( t, x ) for( list< t >::const_iterator iter = ( x ).begin(); iter != ( x ).end(); iter++ )

#endif