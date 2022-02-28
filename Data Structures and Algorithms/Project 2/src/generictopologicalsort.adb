----GenericTopologicalSort.adb----

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Unchecked_Conversion;

----------------GenericTopologicalSort body----------------
package body GenericTopologicalSort is -- This should read (get) the relations and print (put) the results.
   type Node;
   type NodePointer is access Node;
   type Node is tagged record

      Next: NodePointer;
   end record;
   
   type JobElement is tagged record
      Item: SortElement;
      Knt: Integer := 0; -- This field should be used for counting and as queue links.
      Precedent, Successor: JEPointer;
   end record;
   type JEPointer is access JobElement;
   
   --  SortStructure: Array(SortElement) of JobElement;
   
   Pointer: NodePointer;
   RKnt, Remaining, Kntr, F, R, K: Integer;
   --Precedent, Successor : SortElement;
   
   function PTI is new Ada.Unchecked_Conversion(NodePointer, Integer);
   function ITP is new Ada.Unchecked_Conversion(Integer, NodePointer);
   
   ----------------Procedure for TopologicalSort----------------
   procedure TopologicalSort is
   begin
     -- for A in 1..ITemKnt
      --loop
        -- SortStructure(A).Knt := 0;
         --SortStructure(A).Top := null;
      --end loop;
     
      Remaining := ItemKnt;
      Kntr := 1;
      put_line("How many relations are there? ");
      get(RKnt);
     
      for A in 1..RKnt
      loop
         Pointer := new Node;
         put_line("Enter the Precedent followed by its Successor: ");
         put(A); put_line(", ");
         get(Precedent); get(Successor);
         
         --SortStructure(SortElement'Pos(Successor)).Knt :=
           --SortStructure(SortElement'Pos(Successor)).Knt + 1;
         --Pointer.Suc := Successor;
         --Pointer.Next := SortStructure(SortElement'Pos(Precedent)).Top;
         --SortStructure(SortElement'Pos(Precedent)).Top := Pointer;
         exit when Kntr = RKnt;
         
         Kntr := Kntr + 1;
      end loop;
     
      R := 0;
      SortStructure(0).Knt := 0;
     
      for K in 1..ItemKnt
      loop
         if
           (SortStructure(K).Knt = 0)
         then
            SortStructure(R).Knt := K;
            R := K;
         end if;
      end loop;  
   
   end TopologicalSort;

   ----------------Procedure for Result----------------
   procedure Result is
   begin
      F := SortStructure(0).Knt;  
      if Remaining /= 0
      then
         put_line("There is no Solution. The loop potentailly causing the problem is: ");
         for K in 1..ItemKnt
         loop
            SortStructure(K).Knt := 0;
         end loop;

         for K in 1..ItemKnt
         loop
            Pointer := SortStructure(K).Top;
            SortStructure(K).Top := ITP(0); --null????
            while Pointer /= ITP(0) and then
              (SortStructure(SortElement'Pos(Pointer.Suc)).Knt = 0)
            loop
               SortStructure(SortElement'Pos(Pointer.Suc)).Knt := K;
               if (Pointer /= ITP(0))
               then
                  Pointer := Pointer.Next;
               end if;
            end loop;
         end loop;
               
         --  loop
         --  loop
         --   put(SortElement'Val(F));
         --   new_line(1);
         --    Remaining := Remaining - 1;
         --   Pointer := SortStructure(F).Top;
         --   SortStructure(F).Top := ITP(0);
         --   while (Pointer /= ITP(0))
         --   loop
         --      SortStructure(SortElement'Pos(Pointer.Suc)).Knt :=
         --        SortStructure(SortElement'Pos(Pointer.Suc)).Knt - 1;
         --      if (SortStructure(SortElement'Pos(Pointer.Suc)).Knt = 0)
         --      then
         --         SortStructure(R).Knt := SortElement'Pos(Pointer.Suc);
         --        R := SortElement'Pos(Pointer.Suc);
         --      end if;
         --     Pointer := Pointer.Next;
         --    end loop;
         --     F := SortStructure(F).Knt;
         --  end loop;
         --   new_line(2);
         --  end loop;
         --  end if;
         -- end loop;        

         K := 1;
         while (SortStructure(K).Knt = 0)
         loop
            K := K + 1;
         end loop;

         loop
            SortStructure(K).Top := ITP(1);
            K := SortStructure(K).Knt;
            exit when SortStructure(K).Top /= ITP(0); --null???
         end loop;

         while SortStructure(K).Top /= ITP(0)
         loop
            put(SortElement'Val(K)); put(", ");
            SortStructure(K).Top := ITP(0); --null????
            K := SortStructure(K).Knt;
         end loop;

         put(SortElement'Val(K));
         
         put_line("This is a topological sort");
         new_line(1);
      end if;
   end Result;

end GenericTopologicalSort;
