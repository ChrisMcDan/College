with Ada.Text_IO, Ada.Integer_Text_IO; use Ada.Text_IO;
with List_Package; use List_Package;
with MakeCar, MakePlane, MakeInteger; use MakeCar, MakePlane, MakeInteger;

procedure Main is
   type CPointer is access Container;
   VehicleStack, IntegerStack: CPointer := new Container;
   NewMyInt, NewCar, NewPlane, IntegerPt, VehiclePt: CElementPtr;

   NewArray: Array(1..ListSize(VehicleStack.all)) of CPointer;
   NewArray1: Array(1..ListSize(IntegerStack.all)) of CPointer;
   
begin
   --C option data
   --a)	Insert 33 in front (right).
   NewMyInt := new MyInt'(CElement with 33);
   InsertFront(IntegerStack, NewMyInt);
   
   --b)	Insert 57 in front (right) 
   NewMyInt := new MyInt'(CElement with 57);
   InsertFront(IntegerStack, NewMyInt);
   
   --c)	Insert 85 at the rear (left).
   NewMyInt := new MyInt'(CElement with 85);
   InsertRear(IntegerStack, NewMyInt);
   
   --d)	Insert 62 at the rear (left).
   NewMyInt := new MyInt'(CElement with 62);
   InsertRear(IntegerStack, NewMyInt);
   
   --e)	Insert 95 at the front (right).
   NewMyInt := new MyInt'(CElement with 95);
   InsertFront(IntegerStack, NewMyInt);
   
   --f)	Print the contents of the list from front (right) to rear (left).
   put_line("Contents of Integer list from front to rear: ");
   for I in reverse 1..ListSize(IntegerStack.all)
   loop
      IntegerPt  := FindItem(IntegerStack, I);
      PrintItem(IntegerStack, IntegerPt);
   end loop;
   new_line(2);
   
   --g)	Print the content of the list from rear (left) to front (right).
   put_line("Contents of Integer list from rear to front: ");
   for I in 1..ListSize(IntegerStack.all)
   loop
      IntegerPt  := FindItem(IntegerStack, I);
      PrintItem(IntegerStack, IntegerPt);
   end loop;
   new_line(2);
   
   --h)	Find and delete the node containing 57.
   IntegerPt := FindItem(IntegerStack, 4);
   Delete(IntegerStack, IntegerPt);
   
   --i)	Find and delete the node containing 33.
   IntegerPt := FindItem(IntegerStack, 3);
   Delete(IntegerStack, IntegerPt);

   --k)	Find and delete the node containing 62.
   IntegerPt := FindItem(IntegerStack, 1);
   Delete(IntegerStack, IntegerPt);
   
   --l)	Insert 22 in front (right).
   NewMyInt := new MyInt'(CElement with 22);
   InsertFront(IntegerStack, NewMyInt);
   
   --m)	Delete the node containing 95.
   IntegerPt := FindItem(IntegerStack, 2);
   Delete(IntegerStack, IntegerPt);
   
   --n)	Print the contents of the list from front (right) to rear (left).
   put_line("Final contents of Integer list from front to rear: ");
   for I in reverse 1..ListSize(IntegerStack.all)
   loop
      IntegerPt  := FindItem(IntegerStack, I);
      PrintItem(IntegerStack, IntegerPt);
   end loop;
   new_line(2); 
   
   --B option data
   --Cars
   --a) Insert a Ford with 4 doors at the rear (left).
   NewCar := new Car'(CElement with 4, "Ford ");
   InsertRear(VehicleStack, NewCar);
   
   --b)	Insert a Ford with 2 doors at the front (right).
   NewCar := new Car'(CElement with 2, "Ford ");
   InsertFront(VehicleStack, NewCar);
   
   --c) Insert a GMC with 2 doors at the rear (left).
   NewCar := new Car'(CElement with 2, "GMC  ");
   InsertRear(VehicleStack, NewCar);
   
   --d) Insert a RAM with 2 doors at the rear (left).
   NewCar := new Car'(CElement with 2, "RAM  ");
   InsertRear(VehicleStack, NewCar);
   
   --e) Insert a Chevy with 3 doors at the front (right).
   NewCar := new Car'(CElement with 3, "Chevy");
   InsertFront(VehicleStack, NewCar);
   
   --f) Print the number of items in the list.
   put_line("Number of items in the below list: " & Integer'Image(ListSize(VehicleStack.all)));
   new_line(1);
   
   --g) Print the contents of the list (front (right) to rear (left)).   
   put_line("Contents of Car list from front to rear: ");
   for I in reverse 1..ListSize(VehicleStack.all)
   loop
      VehiclePt  := FindItem(VehicleStack, I);
      PrintItem(VehicleStack, VehiclePt);
   end loop;
   new_line(2);
   
   --h) Find and delete the first Ford in the list (search front (right) to rear (left)).
   VehiclePt := FindItem(VehicleStack, 4);
   Delete(VehicleStack, VehiclePt);
   
   --i) Print the number of items in the list.
   put_line("Number of items in the below list: " & Integer'Image(ListSize
            (VehicleStack.all)));
   new_line(1);
   
   --j) Print the contents of the list (front (right) to rear (left)).
   put_line("Contents of Car list from front to rear: ");
   for I in reverse 1..ListSize(VehicleStack.all)
   loop
      VehiclePt := FindItem(VehicleStack, I);
      PrintItem(VehicleStack, VehiclePt);
   end loop;
   new_line(2);
   
   --Planes
   --k) Insert a plane with 3 doors and 6 engines by Boeing at the front (right).
   NewPlane := new Plane'(CElement with 3, 6, "Boeing  ");
   InsertFront(VehicleStack, NewPlane);
   
   --l) Insert a plane with 2 doors and 1 engine by Piper at the front (right).
   NewPlane := new Plane'(CElement with 2, 1, "Piper   ");
   InsertFront(VehicleStack, NewPlane);
   
   --m) Insert a plane with 4 doors and 4 engines by Cessna at the front (right).
   NewPlane := new Plane'(CElement with 4, 4, "Cessna  ");
   InsertFront(VehicleStack, NewPlane);   
    
   --Not an option, but performed for output conformity
   put_line("Number of items in the below list: " & Integer'Image(ListSize
            (VehicleStack.all)));
   new_line(1);
   
   --n) Print the final list.
   put_line("Final contents of Car and Plane list: ");
   for I in reverse 1..ListSize(VehicleStack.all)
   loop
      VehiclePt := FindItem(VehicleStack, I);
      PrintItem(VehicleStack, VehiclePt);
   end loop;
   
end Main;
