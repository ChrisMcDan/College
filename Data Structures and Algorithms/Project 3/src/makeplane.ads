with List_Package;

package MakePlane is
   type String8 is new String(1..8);

   type Plane is new List_Package.DLLElement with record
      NumDoors:  integer;
      NumEngines:  integer;
      Manufacturer: String8 := "Boeing  ";
   end record;
 
   procedure AssignNumDoors(aPlane: in out Plane; N: in integer); 

   procedure AssignManufacturer(aPlane: in out Plane; Manu: in String8); 
 
   procedure AssignNumEngines(aPlane: in out Plane; NE: in integer);

   procedure PrintPlane(aPlane: in Plane); 

   procedure IdentifyVehicle(aPlane: in Plane); 
   
end MakePlane;
