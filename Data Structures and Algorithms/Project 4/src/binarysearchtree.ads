with Ada.Sequential_IO;
with Ada.Text_IO; use Ada.Text_IO
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO
with GenericStack;

generic
   type Akey is private;
   type BinarySearchTreeRecord is private;
   --These functions compare two nodes in the tree.
   with function "<"(TheKey:  in Akey;  ARecord: in BinarySearchTreeRecord)
                     return Boolean;  --Is TheKey less than the key of ARecord?
   with function ">"(TheKey:  in Akey;  ARecord: in BinarySearchTreeRecord) 
                     return Boolean; --Is TheKey greater than the key of ARecord?
   with function "="(TheKey:  in Akey;  ARecord: in BinarySearchTreeRecord) 
                     return Boolean;  --Is TheKey equal to the key of ARecord?
   with procedure putRecord (ARecord : in BinarySearchTreeRecord);
   with procedure putName (Name : in AKey);
   with function getName (ARecord : in BinarySearchTreeRecord) return AKey;
   with function makeRecord (P : in Akey; Q : in AKey) return BinarySearchTreeRecord;
   with function getVal (P : in AKey) return Integer;

   fake : AKey;
   
package BinarySearchTree is
   

   type BinarySearchTreePoint is limited private;
   
   package KeyIO is new Ada.Sequential_IO(AKey); use KeyIO;
   
   --This procedure inserts a node (customer) into the tree in search tree order.
   procedure InsertBinarySearchTree(Root:  in out BinarySearchTreePoint;
                                    CustomerName: in AKey; CustomerPhone: AKey );
   
   --This procedure locates a customer using a binary search.
   procedure FindCustomerIterative(Root: in BinarySearchTreePoint; 
                                   CustomerName:  in AKey;
                                   CustomerPoint:  out BinarySearchTreePoint);
   
   --This procedure locates a customer using a binary search.
   procedure FindCustomerRecursive(Root: in BinarySearchTreePoint; 
                                   CustomerName:  in AKey;
                                   CustomerPoint:  out BinarySearchTreePoint);
   

   --This is sometimes called an iteration function (no recursion).
   function InOrderSuccessor(TreePoint: in BinarySearchTreePoint) 
                             return BinarySearchTreePoint;
   
   --Procedures utilizing threads that prints the name fields of the tree in
   --preorder from within the procedure as it traverses the nodes.
   procedure PreOrderRecursive (P : in out BinarySearchTreePoint);
   procedure PreOrderIterative(TreePoint: in out BinarySearchTreePoint; 
                               Root : in BinarySearchTreePoint);
   
   --Procedures to traverse the tree utilizing threads printing the name fields.
   --You may assume traversal will always start at the root.
   procedure PostOrderIterative(TreePoint: in out BinarySearchTreePoint);
   procedure PostOrderRecursive(TreePoint: in out BinarySearchTreePoint);
   
   --Procedure that generates binary tree.
   procedure makeTree(file : String);
   
   --Procedure that allocates node that goes to tree.
   procedure allocateNode (Q : out BinarySearchTreePoint; 
                           name: in AKey; number : in AKey);
   
   --Procedure that inserts node into binary search tree.
   procedure insertNode (P : in out BinarySearchTreePoint; 
                         Q : in out BinarySearchTreePoint; name : in Akey; 
                         number : in Akey);
  
   --Procedure that traverses the tree starting at the root.
   procedure ReverseInOrder (P : in out BinarySearchTreePoint);
   
   --Procedure that deletes a random node within the tree.
   procedure DeleteRandomNode(Q : in out BinarySearchTreePoint; 
                              Root : in out BinarySearchTreePoint);
   
private
   type Node;
   type BinarySearchTreePoint is access Node;
   type Node is 
      record
         Llink, Rlink : BinarySearchTreePoint := null;
         Ltag, Rtag : Boolean := false; --True indicates pointer to lower level, False a thread.
         Info : BinarySearchTreeRecord;
      end record;
   
   type stackRec is
      record
         Number : Integer;
         Point : BinarySearchTreePoint;
      end record;
end BinarySearchTree;
