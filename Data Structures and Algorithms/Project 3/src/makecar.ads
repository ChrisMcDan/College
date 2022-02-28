with List_Package;

package MakeCar is
   
   type String5 is new String(1..5);
   
   type Car is new List_Package.DLLElement with
      record
         NumDoors: integer;
         Manufacturer: String5;
      end record;
   
   procedure AssignNumDoors(aCar: in out Car; N: in integer); 

   procedure AssignManufacturer(aCar: in out Car; Manu: in String5); 
 
   procedure PrintNumDoors(aCar: in Car); 

   procedure PrintManufacturer(aCar: in Car); 

   procedure IdentifyVehicle(aCar: in Car);

end MakeCar;
