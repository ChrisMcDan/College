with List_Package;

package MakeInteger is

   type MyInt is new List_Package.CElement with
      record
         Digit: integer;
      end record;
   
   procedure AssignDigit(aMyInt: in out MyInt; D: in integer);
   
   procedure IdentifyDigit(aMyInt: in MyInt);

end MakeInteger;
