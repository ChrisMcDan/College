with Ada.Text_IO; use Ada.Text_IO;
with ada.Unchecked_Deallocation;
with Unchecked_Conversion;
with MakeCar, MakePlane; use MakeCar, MakePlane;

package body List_Package is
   
   Char_Size : Natural := (DLLElementPtr'Size / Character'Size);
   function EmptyBuffer is new Unchecked_Conversion(DLLElementPtr, DLLNodePtr);
   
   --Provide opportunity for garbage collection and reuse of Nodes.
   procedure Free is new Ada.Unchecked_Deallocation(DLLElement, DLLNodePtr); --Reclaim heap storage
   
   --Gets list size
   function ListSize (list: Integer_Container) return Integer is
   begin
      return List.Knt;
   end ListSize;
   
   --This will insert an element into the front of the list
   procedure InsertFront(list: access Integer_Container; amt: in DLLElementPtr) is
      PtrTop, PtrMain : DLLElementPtr := List.Top;
      IfKnt, ValueKnt : Integer := 0;
   
   begin
      if List.Top = null then
         List.Top := amt;
         List.Bottom := List.Top;
         amt.Previous := null;
         amt.Next := null;
      else
         amt.Next := List.Top;
         List.Top.Previous := amt;
         List.Top := amt;
         amt.Previous := null;
      end if;
      
      List.Knt := List.Knt + 1;
      IfKnt := IfKnt + 1;
      amt.Value := 1;
      PtrTop := amt;
      PtrMain := amt;
      
      while IfKnt > ValueKnt
      loop
         PtrTop := PtrTop.Next;
         ValueKnt := ValueKnt + 1;
      end loop;
      
      while PtrTop /= null
      loop
         PtrMain := PtrMain.Next;
         PtrTop := PtrTop.Next;
         PtrMain.Value := PtrMain.Value + 1;
      end loop;
   end InsertFront;
   
   --This will insert an element into the rear of the list
   procedure InsertRear(list: access Integer_Container; amt: in DLLElementPtr) is
   begin
      if List.Top = null then
         List.Bottom := amt;
         List.Top := List.Bottom;
         amt.Next := null;
         amt.Previous := null;
      else
         amt.Previous := List.Bottom;
         List.Bottom.Next := amt;
         List.Bottom := amt;
         amt.Next := null;
      end if;
   
      List.Knt := List.Knt + 1;
   
      amt.Value := List.Knt;
   end InsertRear;
   
   --This will delete an element from the Doubly Linked list
   procedure Delete(list: access Integer_Container; amt: in out DLLElementPtr) is
      PtrTop: DLLElementPtr := List.Top;
   begin
      if List.Top = null or amt = null then
         put_line("Empty List or AMT");
      else
         if amt.Previous = null or List.Top = amt then
            List.Top := amt.Next;
         else
            amt.Previous.Next := amt.Next;
         end if;
      
         if amt.Next = null then
            List.Bottom := amt.Previous;
         else
            amt.Next.Previous := amt.Previous;
         end if;
         
         List.Knt := List.Knt - 1;
         
         PtrTop := amt;
         
         for I in amt.Value..List.Knt
         loop
            PtrTop := PtrTop.Next;
            PtrTop.Value := PtrTop.Value - 1;
         end loop;
      end if;
   end delete;
   
   --This will print the element the pointer is pointing to
   procedure PrintItem (list: access Integer_Container; amt: DLLElementPtr) is
      PtrTop: DLLElementPtr := List.Top;
      Knt: Integer := 0;
   begin
      if List.Top = null then
         put_line("Underflow");
      else
         put_line("Contents of the list" & Integer'Image(amt.Value) & ": ");
         if amt.all in Car then
            IdentifyVehicle(Car'Class(amt.all));
         elsif amt.all in Plane then
            IdentifyVehicle(Plane'Class(amt.all));
         end if;
         new_line(1);
      end if;
   end PrintItem;
     
   --This will Find an element in the list
   function FindItem(list: access Integer_Container; aValue: Integer) return DLLElementPtr is
      PtrTop, PtrMain : DLLElementPtr := List.Top;
      Knt: Integer := 0;
   begin
      if List.Top = null then return null;
      else
         while Knt < aValue
         loop
            PtrMain := PtrMain.Next;
            Knt := Knt + 1;
         end loop;
         while PtrMain /= null
         loop
            PtrMain := PtrMain.Next;
            PtrTop := PtrTop.Next;   
         end loop;
         return PtrTop;
      end if;
   end FindItem;
   
   --This will find and return the following pointer of an item
   function NextItem(list: access Integer_Container; aValue: Integer) return DLLElementPtr is
      PtrTop, PtrMain: DLLElementPtr := List.Top;
      Knt: Integer := 0;
   begin
      if List.Top = null then return null;
      else
         while aValue > Knt
         loop
            PtrMain := PtrMain.Next;
            Knt := Knt + 1;
         end loop;
         while PtrMain /= null
         loop
            PtrMain := PtrMain.Next;
            PtrTop := PtrTop.Next;
         end loop;
         return PtrTop.Next;
      end if;
   end NextItem;
      
   --This will pop the element from the top of the list
   function Pop(list: access Integer_Container) return DLLElementPtr is
      amt: DLLElementPtr;
      EmptyElement: DLLNodePtr;
   begin
      if List.Top = null then --Checks for underflow
         return null;
      else
         amt := List.Top; --Pop stack, note hemorrhaging
         List.Top := List.Top.Next; --Pop stack, note hemorrhaging.
         EmptyElement := EmptyBuffer(amt);
         Free(EmptyElement); --Memory hemorrhaging occurs if forgotten
         List.Knt := List.Knt - 1; --Removes 1 from list knt
         return amt;
      end if;
   end Pop;
   
end List_Package;
