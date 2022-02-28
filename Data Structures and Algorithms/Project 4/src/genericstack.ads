generic
   max : integer; --Max size of stack.
   type MyType is private; --Type that goes into stack.
   
package GenericStack is
   procedure push(x: in MyType); --Push procedure defintion.
   procedure pop(x: out MyType); --Pop procedure definition.
   function Empty return Boolean; --Function to say when the stack is empty.
end GenericStack;
