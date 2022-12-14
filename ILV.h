/*
 * ILV.h
 *
 *  Created on: Mar 4, 2021
 *      Author: Islam Ahmed
 */

#ifndef ILV_H_
#define ILV_H_






#include "Commons.h"




       uint32 IL16V_BuildPacket( uint8 Identifire , uint16 Length , const uint8* Value, uint8* Destination);
       uint32 IL32V_BuildPacket( uint8 Identifire , uint32 Length , const uint8* Value, uint8* Destination);
       uint16 IL16V_GetDataLength( const uint8* ILVPacket);
       uint32 IL32V_GetDataLength( const uint8* ILVPacket);
       uint32 IL16V_IL32V_GetDataLength(const uint8* ILVPacket);
       uint32 ILV_GetData(const uint8* ILVPacket , uint8* Destination);
      
	  
	   #define ILV_GetIdentifier(ILVPacket)   ((ILVPacket)[0])
	    
         
           
        




#endif /* ILV_H_ */