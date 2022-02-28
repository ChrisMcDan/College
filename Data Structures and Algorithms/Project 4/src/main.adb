with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with BinarySearchTree;

procedure Main is
   type AKey is new string(1..10);
   type BinarySearchTreeRecord is record
      Name: AKey;
      PhoneNumber: AKey;
   end record;

   function "<"(TheKey:  in Akey;  ARecord: in BinarySearchTreeRecord)
                  return Boolean is  --Is TheKey less than the key of ARecord?
   begin
      if TheKey < ARecord.name then
         return true;
      else
         return false;
      end if;
   end "<";

   function ">"(TheKey:  in Akey;  ARecord: in BinarySearchTreeRecord)
                return Boolean is --Is TheKey greater than the key of ARecord?
   begin
      if TheKey > ARecord.name then
         return true;
      else
         return false;
      end if;
   end ">";

   function "="(TheKey:  in Akey;  ARecord: in BinarySearchTreeRecord)
                return Boolean is  --Is TheKey equal to the key of ARecord?
  begin
      if TheKey = ARecord.name then
         return true;
      else
         return false;
      end if;
   end "=";

   procedure putRecord (ARecord : in BinarySearchTreeRecord) is
   begin
      put(ARecord.Name);
      put(" -- ");
      put(ARecord.PhoneNumber);
      new_line(1);
      end putRecord;

   procedure putName (Name : in AKey) is
   begin
      put(Name);
   end putName:

   function getName (ARecord : in BinarySearchTreeRecord) return AKey is
   begin
      return ARecord.Name;
   end getName;

   function makeRecord (P : in Akey; Q : in AKey) return BinarySearchTreeRecord is
      Rec : Customer := (P, Q);
   begin
      return Rec;
   end makeRecord;

   function getVal (P : in AKey) return Integer is
   begin
      return Integer'Value(P);
   end getVal;


   package BSTree is new BinarySearchTree(AKey, BinarySearchTreeRecord,
                                                      "<", ">", "=", putRecord,
                                                      putName, getName, makeRecord,
                                                      getVal);
begin
   put_line("----- 'C' Option Transactions-----");
   new_line(1);

   --Step 1
   BSTree.insertNode("Moutafis  ", "295-1492  ");
   BSTree.insertNode("Ikerd     ", "291-1864  ");
   BSTree.insertNode("Gladwin   ", "295-1601  ");
   BSTree.insertNode("Robson    ", "293-6122  ");
   BSTree.insertNode("Dang      ", "295-1882  ");
   BSTree.insertNode("Bird      ", "291-7890  ");
   BSTree.insertNode("Harris    ", "294-8075  ");
   BSTree.insertNode("Ortiz     ", "584-3622  ");

   --Step 2
   put_line(BSTree.CustomerPhone(BSTree.FindCustomerIterative("Ortiz     ")));

   --Step 3
   put_line(BSTree.CustomerPhone(BSTree.FindCustomerRecursive("Ortiz     ")));

   --Step 4
   put_line(BSTree.CustomerPhone(BSTree.FindCustomerIterative("Penton    ")));

   --Step 5
   put_line(BSTree.CustomerPhone(BSTree.FindCustomerRecursive("Penton    ")));
   new_line(1);

   --Step 6
   put_line("InOrder Traversal starting at Ikerd: ");
   BSTree.InOrderSuccessor("Ikerd     ");
   new_line(1);

   --Step 7
   BSTree.insertNode("Avila     ", "294-1568  ");
   BSTree.insertNode("Quijada   ", "294-1882  ");
   BSTree.insertNode("Villatoro ", "295-6622  ");
   new_line(1);

end Main;
