package body BinarySearchTree is

   --This procedure inserts a node (customer) into the tree in search tree order.
   --Page 94 of DS Notes.
   procedure InsertBinarySearchTree(Root:  in out BinarySearchTreePoint;
                                    CustomerName: in AKey; CustomerPhone: AKey ) is
      P, T : BinarySearchTreePoint; 
   begin
      if Root = null then --Empty tree, so insert as the root of the tree.
         put_line("Inserting new root of tree");
         allocateNode(T, CustomerName, CustomerPhone);
         Root := T;
      else --Tree is not empty.  Locate a match with existing node or position to insert new node.
         put_line("Inserting");
         P := Root;
         loop --Search left and right for a match or insert in tree if not found.
            if CustomerName < P.Info then  --Search to left.
               if P.LTag then
                  P := P.Llink;
               else
                  allocateNode(T, CustomerName, CustomerPhone); --Insert node as left subtree.
                  insertNode(P, T, CustomerName, CustomerPhone);
                  putRecord(T.Info);
                  exit; --New node inserted.
               end if;
            elsif CustomerName > P.Info then
               if P.RTag then
                  P := P.Rlink;
               else
                  allocateNode(T, CustomerName, CustomerPhone); --Insert node as right subtree.
                  insertNode(P, T, CustomerName, CustomerPhone);
                  putRecord(T.Info);
                  exit; --New node inserted.
               end if;
            end if;
         end loop;
      end if;
   end InsertBinarySearchTree;
   
   --Procedure that allocates node that goes to tree.
   --Page 94 of DS Notes.
   procedure allocateNode (Q : out BinarySearchTreePoint; 
                           name: in AKey; number : in AKey) is
   begin --Allocates and places AKey in node pointed to by Q.
      Q := new Node'(null, null, false, true, makeRecord(name, number));
      Q.Llink := Q;
      Q.Llink := Q.Rlink;
   end allocateNode;
      
   --Procedure that inserts node into binary search tree.
   --Page 94 of DS Notes.
   procedure insertNode(P : in out BinarySearchTreePoint; 
                        Q : in out BinarySearchTreePoint;
                        name : in Akey; number : in Akey) is
   begin --Inserts the Node pointed to by Q as a subtree of P.
      if name < P.Info then --Insert Akey as left subtree of P.
         if getName(P.Info) /= fake then
            put_line("Left subtree of ");
            putName(getName(P.Info));
            New_Line(1);
         else
            put_line("New root node added.");
         end if;
         Q.Ltag := P.Ltag;
         Q.Llink := P.Llink;
         P.Ltag := true;
         Q.Rtag := false;
         P.Llink := Q;
         Q.RLink := P;
      else --Insert Akey as right subtree of P.
         if getName(P.Info) /= fake then
            Put_Line("Right subtree of ");
            putName(getName(P.Info));
            New_Line(1);
         else
            Put_Line("New root node added.");
         end if;
         Q.Rtag := P.Rtag;
         Q.Rlink := P.Rlink;
         P.Rtag := true;
         Q.Ltag := false;
         P.Rlink := Q;
         Q.Llink := P;
      end if;
   end insertNode;
   
   --This procedure locates a customer using a binary search.
   procedure FindCustomerIterative(Root: in BinarySearchTreePoint; 
                                   CustomerName:  in AKey;
                                   CustomerPoint:  out BinarySearchTreePoint) is
   begin
   
   end FindCustomerIterative;

   --This procedure locates a customer using a binary search.
   procedure FindCustomerRecursive(Root: in BinarySearchTreePoint; 
                                   CustomerName:  in AKey;
                                   CustomerPoint:  out BinarySearchTreePoint) is
   begin
      
   end FindCustomerRecursive;
   

   --This is sometimes called an iteration function (no recursion).
   function InOrderSuccessor(TreePoint: in BinarySearchTreePoint) 
                             return BinarySearchTreePoint is
      stack: array(1..max) of BinarySearchTreePoint;
      knt: integer;
      pt: BinarySearchTreePoint;
   begin
      knt := 0;
      pt := TreePoint; --Set stack empty, pt to the root of the tree.
      loop
         if pt /= null then
            knt := knt + 1;
            stack(knt) := pt;
            pt := pt.Left;
         else
            exit when knt = 0; --Traversed the whole tree.
            pt := stack(knt);
            knt := knt - 1;
            put ("tree sort ");
            put (pt.Value);
            new_line(1);
            pt := pt.Right;
         end if;
      end loop;
   end InOrderSuccessor;
   
   --Procedures utilizing threads that prints the name fields of the tree in
   --preorder from within the procedure as it traverses the nodes.
   procedure PreOrderRecursive (P : in out BinarySearchTreePoint) is
   begin
      
   end PreOrderRecursive;
         
   procedure PreOrderIterative(TreePoint: in out BinarySearchTreePoint; 
                               Root : in BinarySearchTreePoint) is
   begin
      
   end PreOrderIterative;
         
   --Procedures to traverse the tree utilizing threads printing the name fields.
   --You may assume traversal will always start at the root.
   procedure PostOrderIterative(TreePoint: in out BinarySearchTreePoint) is
      P, T : BinarySearchTreePoint := TreePoint;
      package gStack is new GenericStack(50, BinarySearchTreePoint);
   begin
      put_line("Traversing, iteratively, in postorder: ");
      P := PostOrderSucccessor(T);
      gStack.push(P);
      P := PostOrderSuccessor(P);
      while P /= T
      loop
         gStack.push(P);
      end loop;
      
      while not gStack.Empty
      loop
         gStack.pop(P);
         putRecord(P.Info);
      end loop;
      putRecord(TreePoint.Info);
   end PostOrderIterative;
               
   procedure PostOrderRecursive(TreePoint: in out BinarySearchTreePoint) is
   begin
      if TreePoint.Ltag then
         PostOrderRecursive(TreePoint.Llink);
      end if;
      if TreePoint.Rtag then
         PostOrderRecursive(TreePoint.Rlink);
      end if;
      putRecord(TreePoint.Info);
   end PostOrderRecursive;
         
   --Procedure that generates binary tree.
   procedure makeTree(file : String) is
   begin
      
   end makeTree;
   
   --Procedure that traverses the tree starting at the root.
   --Page 81 of DS notes, just do the algorithm in reverse.
   procedure ReverseInOrder (TreePoint : in out BinarySearchTreePoint) is
   begin
      if TreePoint.RTag then
         ReverseInOrder(TreePoint.Rlink);
      end if;
      if TreePoint.Ltag then
         ReverseInOrder(TreePoint.Llink);
      end if;
      putRecord(TreePoint.Info);
   end ReverseInOrder;
   
   --Procedure that deletes a random node within the tree.
   procedure DeleteRandomNode(Q : in out BinarySearchTreePoint; 
                              Root : in out BinarySearchTreePoint)is
   begin
      T := Q;
      if T.Rlink = null then
         Q := T.Llink;
         T := Avail;
      else
         if T.Llink = null then --Easy delete if Llink = Null
            Q := T.Rlink;
            T := Avail;
         end if;
         --Find successor in inorder
         R := T.Rlink; --From semetry, step one node to right, search left if required.
         if R.Llink = null then --Found the inorder successor.
            R.Llink := T.Llink;
            Q := R;
            T := Avail;
         else
            S := R.Llink; --Search to the left looking for null LLink.
            while S.Llink /= null
            loop
               R := S;
               S := R.Llink;
            end loop; --At this point S will be the inorder successor of Q.
            S.Llink := T.Llink;
            R.Llink := S.Rlink;
            S.Rlink := T.Rlink;
            Q := s;
            T := Avail;
         end if;
      end if;
      if P = Root then
         Root := Q;
      else --Assumes we have deleted the first node in the left or right subtree of P.
         if deleting P.Llink then
            P.Llink := Q;
         else
            P.Rlink := Q;
         end if;
      end if;
   end DeleteRandomNode;
   
end BinarySearchTree;
