with Ada.Text_IO, Ada.Integer_Text_IO; use Ada.Text_IO;
with List_Package; use List_Package;
with MakeCar, MakePlane; use MakeCar, MakePlane;

procedure UAbstStc is
   type DLLPointer is access Integer_Container;
   VehicleStack: DLLPointer := new Integer_Container;
   NewCar, NewPlane, VehiclePt: DLLElementPtr;
   
   task type Buffer is
      entry Insert (VehiclePt: in DLLElementPtr);
      entry Remove (VehiclePt: out DLLElementPtr);
   end Buffer;
   
   task body Buffer is
      Point1: DLLElementPtr;
   begin
      accept Insert (VehiclePt: in DLLElementPtr)
      do
         Point1 := VehiclePt;
      end Insert;
      loop
         select
            accept Insert (VehiclePt: in DLLElementPtr)
            do
               Point1 := VehiclePt;
            end Insert;
         or
            accept Remove (VehiclePt: out DLLElementPtr)
            do
               VehiclePt := Point1;
            end Remove;
         end select;
      end loop;
   end Buffer;

   type PtrBuffer is access Buffer;
   type InsertArray is array (Integer range <>) of PtrBuffer;
   NewArray: InsertArray(1..ListSize(VehicleStack.all));
   
begin
   --Cars
   --a) Insert a Ford with 4 doors at the rear.
   NewCar := new Car;
   AssignNumDoors(Car'Class(NewCar.all), 4);
   AssignManufacturer(Car'Class(NewCar.all), "Ford ");
   InsertRear(VehicleStack, NewCar);

   
   --b)	Insert a Ford with 2 doors at the front.
   NewCar := new Car;
   AssignNumDoors(Car'Class(NewCar.all), 2);
   AssignManufacturer(Car'Class(NewCar.all), "Ford ");
   InsertFront(VehicleStack, NewCar);
   
   --c) Insert a GMC with 2 doors at the rear.
   NewCar := new Car;
   AssignNumDoors(Car'Class(NewCar.all), 2);
   AssignManufacturer(Car'Class(NewCar.all), "GMC  ");
   InsertRear(VehicleStack, NewCar);
   
   --d) Insert a RAM with 2 doors at the rear.
   NewCar := new Car;
   AssignNumDoors(Car'Class(NewCar.all), 2);
   AssignManufacturer(Car'Class(NewCar.all), "Ram  ");
   InsertRear(VehicleStack, NewCar);
   
   --e) Insert a Chevy with 3 doors at the front.
   NewCar := new Car;
   AssignNumDoors(Car'Class(NewCar.all), 3);
   AssignManufacturer(Car'Class(NewCar.all), "Chevy");
   InsertFront(VehicleStack, NewCar);
   
   --f) Print the number of items in the list.
   put_line("List size: " & Integer'Image(ListSize(VehicleStack.all)));
   new_line(1);
   
   --g) Print the contents of the list (front to rear).   
   put_line("Current contents of list: ");
   for I in reverse 1..ListSize(VehicleStack.all)
   loop
      VehiclePt  := FindItem(VehicleStack, I); --Remove I?
      PrintItem(VehicleStack, VehiclePt);
   end loop;
   
   --h) Find and delete the first Ford in the list (search front to rear).
   VehiclePt := FindItem(VehicleStack, 4);
   Delete(VehicleStack, VehiclePt);
   
   --i) Print the number of items in the list.
   put_line("Number of items in the list: " & Integer'Image(ListSize
            (VehicleStack.all)));
   new_line(1);
   
   --j) Print the contents of the list (front to rear).
   put_line("Current contents of list: ");
   for I in reverse 1..ListSize(VehicleStack.all)
   loop
      VehiclePt := FindItem(VehicleStack, I); --Remove I?
      PrintItem(VehicleStack, VehiclePt);   
   end loop;
   
   --k) Insert a plane with 3 doors and 6 engines by Boeing at the front.
   NewPlane := new Plane;
   AssignNumDoors(Plane'Class(NewPlane.All), 3);
   AssignNumEngines(Plane'Class(NewPlane.All), 6);
   AssignManufacturer(Plane'Class(NewPlane.all), "Boeing  ");
   InsertFront(VehicleStack, NewPlane);
   
   --l) Insert a plane with 2 doors and 1 engine by Piper at the front.
   NewPlane := new Plane;
   AssignNumDoors(Plane'Class(NewPlane.All), 2);
   AssignNumEngines(Plane'Class(NewPlane.All), 1);
   AssignManufacturer(Plane'Class(NewPlane.all), "Piper   ");
   InsertFront(VehicleStack, NewPlane);
   
   --m) Insert a plane with 4 doors and 4 engines by Cessna at the front.
   NewPlane := new Plane;
   AssignNumDoors(Plane'Class(NewPlane.All), 4);
   AssignNumEngines(Plane'Class(NewPlane.All), 4);
   AssignManufacturer(Plane'Class(NewPlane.all), "Cessna  ");
   InsertFront(VehicleStack, NewPlane);   
   
   --n) Print the list.
   put_line("Current Contents of list: ");
   for I in reverse 1..ListSize(VehicleStack.all)
   loop
      VehiclePt := FindItem(VehicleStack, I); --Remove I?
      PrintItem(VehicleStack, VehiclePt);
   end loop;
   
end UAbstStc;
