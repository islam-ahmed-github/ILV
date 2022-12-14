/*
 * ILV.c
 *
 *  Created on: Mar 4, 2021
 *      Author: Islam Ahmed
 */




#include "ILV.h"



/****************************************************** ILV-API *************************************************/



    uint32 IL16V_BuildPacket( uint8 Identifire , uint16 Length , const uint8* Value, uint8* Destination)
    {
            Destination[0]     = Identifire;
            // length is in little endian
            Destination[1] = (uint8)Length;
            Destination[2] = (uint8)(Length>> 8);
            for (uint16 i = 0; i < Length; i++) Destination[3+i] = Value[i];
            return  (Length+3);
    }





        // will return the final full packet length
       uint32 IL32V_BuildPacket( uint8 Identifire , uint32 Length , const uint8* Value, uint8* Destination)
        {


            // command identifier
            Destination[0] = Identifire;

            // escape code >> refer to datasheet
            Destination[1] = 0xFF;
            Destination[2] = 0xFF;

            // length is in little endian
            Destination[3] = (uint8)(Length);
            Destination[4] = (uint8)(Length >> 8);
            Destination[5] = (uint8)(Length >> 16);
            Destination[6] = (uint8)(Length >> 24);

            // copy data
            for (uint32 i = 0; i < Length; i++) Destination[7 + i] = Value[i];
            return (Length+3);

        }



       uint16 IL16V_GetDataLength( const uint8* ILVPacket)
          {
              // little endian format
             uint16 temp = 0;
             temp |=  (((uint16)ILVPacket[2]) << 8);
	         temp |=   ILVPacket[1] ;
	          return temp;
          }



        uint32  IL32V_GetDataLength( const uint8* ILVPacket)
        {
            // little endian format
            uint32 temp = 0;
            temp |= ((uint32)ILVPacket[6] << 24);
            temp |= ((uint32)ILVPacket[5] << 16);
            temp |= ((uint32)ILVPacket[4] << 8);
            temp |= ((uint32)ILVPacket[3]);
            return temp;
        }



        uint32 IL16V_IL32V_GetDataLength(const uint8* ILVPacket)
        {
            uint32 len =  IL16V_GetDataLength(ILVPacket);
            if (len == 0xFF) return IL32V_GetDataLength(ILVPacket); // get ILV32 length
            else return len; //ILV16
        }





      uint32  ILV_GetData(const uint8* ILVPacket , uint8* Destination) // will return the length
        {
            uint32 i = 0;
            uint32 len = IL16V_GetDataLength(ILVPacket);// get ILV16 length
            if (len == 0xFF)// ILV32
            {
                len =  IL32V_GetDataLength(ILVPacket);
                for (i = 0; i < len; i++) Destination[i] = ILVPacket[i+7];
            }
            else // ILV16
            {
                for (i = 0; i < len; i++) Destination[i] = ILVPacket[i+3];
            }
            return len;
        }



     



        /************************************************* END OF ILV-API ******************************************************/