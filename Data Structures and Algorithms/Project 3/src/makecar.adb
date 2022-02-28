with Ada.Text_IO; use Ada.Text_io;
with List_Package;

package body MakeCar is
   package IntIO is new Ada.Text_IO.Integer_IO(Integer);  use IntIO;

   procedure AssignNumDoors(aCar: in out Car; N: in integer) is
   begin 
      aCar.NumDoors := N; 
   end AssignNumDoors;

   procedure AssignManufacturer(aCar: in out Car; Manu: in String5) is
   begin 
      aCar.Manufacturer := Manu; 
   end AssignManufacturer;
 
   procedure PrintNumDoors(aCar: in Car) is
   begin 
      put("Num doors = "); 
      put(aCar.NumDoors); 
      new_line(1); 
   end PrintNumDoors;

   procedure PrintString5(PrtStr: String5) is
   begin for I in 1.. 5 
      loop 
         put(PrtStr(I)); 
      end loop; 
   end PrintString5;

   procedure PrintManufacturer(aCar: in Car) is
   begin 
      put("Manufacturer is "); 
      PrintString5(aCar.Manufacturer); 
      new_line(1); 
   end;

   procedure IdentifyVehicle(aCar: in Car) is
   begin 
      put("Car with "); put(aCar.NumDoors, 4); put(" doors"); 
      put(" made by "); PrintString5(aCar.Manufacturer); 
      new_line(1);
   end IdentifyVehicle; 
   
end MakeCar;
