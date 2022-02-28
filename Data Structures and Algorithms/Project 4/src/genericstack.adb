package body GenericStack is
   stack : array(1..max) of MyType;
   top : integer range 0..max;
   
   procedure Push(x: in MyType) is
   begin
      if(top < max) then
         top := top + 1;
         stack(top) := x;
      end if;
   end Push;

   procedure Pop(x: out MyType) is
   begin
      if(top > 0) then
         x := stack(top);
         top := top - 1;
      end if;
   end Pop;
   
   function Empty return Boolean is
   begin
      return (top = 0);
   end Empty;
   
begin
   top := 0; --Initialize top of the stack to 0.
end GenericStack;
