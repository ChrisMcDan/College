with Ada.Text_IO; use Ada.Text_io;
with List_Package;

package body MakeInteger is
   package IntIO is new Ada.Text_IO.Integer_IO(Integer);  use IntIO;
   
   procedure AssignDigit(aMyInt: in out MyInt; D: in integer) is
   begin
      aMyInt.Digit := D;
   end AssignDigit;
   
   procedure IdentifyDigit(aMyInt: in MyInt) is
   begin
      put("Integer: "); put(aMyInt.Digit, 4);
   end IdentifyDigit;
   
end MakeInteger;
