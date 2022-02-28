package List_Package is --Container stack, stack element, and element pointer types
   type Integer_Container is limited private;
   type DLLElement is tagged private;
   type DLLElementPtr is access all DLLElement'Class; --Inheritance
   
   procedure InsertFront(list: access Integer_Container; amt: in DLLElementPtr);
   procedure InsertRear(list: access Integer_Container; amt: in DLLElementPtr);
   procedure Delete(list: access Integer_Container; amt: in out DLLElementPtr);
   procedure PrintItem(list: access Integer_Container; amt: DLLElementPtr);
   
   function ListSize(list: Integer_Container) return Integer;
   function FindItem(list: access Integer_Container; aValue: Integer) return DLLElementPtr;
   function NextItem(list: access Integer_Container; aValue: Integer) return DLLElementPtr;
   function Pop(list: access Integer_Container) return DLLElementPtr;
   
private
   type DLLNodePtr is access DLLElement; --Define pointer type to Node.
   
   type Integer_Container is limited
      record         
         Knt: Integer := 0; --Used to track the number of items in list
         Top, Bottom: DLLElementPtr := null;    --Front and Rear
      end record;
   
   type DLLElement is tagged  --Allows for heterogenous list via inheritance
      record
         Value: Integer := 0;
         Next, Previous: DLLElementPtr;
      end record;
   
end List_Package;
