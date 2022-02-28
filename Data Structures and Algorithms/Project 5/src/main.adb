with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Float_Text_IO; use Ada.Float_Text_IO;
with Ada.Long_Integer_Text_IO; use Ada.Long_Integer_Text_IO;
with Ada.Numerics.Generic_Elementary_Functions;
with Ada.Unchecked_Conversion;

--Table Size = 128
procedure Main is

   --pragma Suppress(Overflow_Check); --Check for numeric overflow. Constraint_Error suppressed.
   
   --Global variables.
   TempHash : Long_Integer;
   TempKey : String(1..16);
   InputFile: File_Type;
   
   MArray: array (1..128) of Integer; --p: array
   
   type InputData is record
      Key : String(1..16) := "&&&&&&&&&&&&&&&&"; --Empty location
      HA : Long_Integer := 0; --Hash Address.
      Probes : Integer := 0; --Number of probes.
   end record;
   
   Table: array (1..128) of InputData;
   
   String16: String(1..16);

   --Convert character to integer.
   function ConvertString16 is new Ada.Unchecked_Conversion(String, Long_Integer);
   
   package Logarithm is new Ada.Numerics.Generic_Elementary_Functions(Float);
   use Logarithm;
      
   ---------------------------Functions-----------------------------
   --Burris Hash function.
   function BurrisHash(X: in String) return Long_Integer is
      Sum : Long_Integer;
      Divider : Long_Integer := 65535;
   begin
      --HA = {abs[ slice(4..5) ] + abs[slice(13..14) ] } / 65,535 + abs[slice(10..10)]
      Sum := (ConvertString16(String16(4..5))) + (ConvertString16(String16(13..14)));
      Sum:= (Sum / Divider);
      Sum:= (Sum + (ConvertString16(String16(10..10))));
      
      TempHash := ((abs(Sum)) mod 128 + 1); --Folding remainder with table size 128.
      return TempHash;
   end BurrisHash;
   ----------------------------Procedures---------------------------
   
   --Displays the table.
   --Uses records from InputData.
   procedure Display is
      Num : Integer := 1;
      
   begin
      for K of Table
      loop
         put(Num, 0);
         put(".    "); --#.
         put(K.Key);
         put("  Hash Address:"); --#
         put(K.HA);
         put("  Probes:"); --#
         put(K.Probes);
         New_Line(1);
         Num := Num + 1; --Increase Address number (1-128).
      end loop;
   end Display;
   
   --Empties the table for next run through.
   --Resets to original InputData record.
   procedure Empty is
   begin
      for K of Table
      loop
         K.Key := "&&&&&&&&&&&&&&&&"; --Empty location.
         K.HA := 0; --Hash address is 0.
         K.Probes := 0; --Number of probes is 0.
      end loop;
   end Empty;
   
   --Inserts linear probe.
   --Page 144 and 163 of DS Notes.
   procedure InsertLinear (CheckHA: in Long_Integer; Insert: in out InputData) is
      TempHA : Integer;
      
   begin
      --If TempHA = 0, set it to 1.
      if TempHA = 0 then
         TempHA := 1;
         Insert.HA := 1;
      end if;
      
      --If an empty spot is found, insert the Insert.
      if Table(TempHA).HA = 0 then
         Insert.Probes := 1;
         Table(TempHA) := Insert;
      else --Keep looking.
         Insert.Probes := 1;
         while Table(TempHA).HA /= 0
         loop --A collision has occured. Continue linearly until empty spot is found.
            Insert.Probes := Insert.Probes + 1;
            if TempHA < 128 then --HA doesn't exceed the size of the table.
               TempHA := TempHA + 1;
            else
               TempHA := 1;
            end if;
         end loop;
         Table(TempHA) := Insert;
      end if;
   end InsertLinear;
   
   --Generates random numbers for use with random probe.
   --Page 160 of DS Notes.
   procedure GenerateRandomProbe is
      R, K : Integer := 1;
      Done : Boolean := False;
   begin
      while not Done
      loop
         R := (5 * R);
         R := (R mod(2**9)); --Table size of 128
         if R = 1 then --Initialization seed.
            Done := True; --Return initial seed.
         end if;
         MArray(K) := (R / 4); --Set random number = (R/4).
         K := K + 1;
      end loop;
   end GenerateRandomProbe;
   
   --Inserts random probe.
   --Page 144, 162, and 163 of DS Notes.
   procedure InsertRandom (CheckHA: in Long_Integer; Insert: in out InputData) is
      TempHA : Integer;
      Root : Integer;
      K : Integer := 1;
      
   begin      
      --If TempHA = 0, set it to 1.
      if TempHA = 0 then
         TempHA := 1;
         Insert.HA := 1;
      end if;
      
      --If an empty spot is found, insert the Insert.
      if Table(TempHA).HA = 0 then
         Insert.Probes := 1;
         Table(TempHA) := Insert;
      else --Keep looking.
         Insert.Probes := 1;
         while Table(TempHA).HA /= 0
         loop --A collision has occured. Generate a random offset and try again.
            Insert.Probes := Insert.Probes + 1;
            TempHA := Root + MArray(K);
            if TempHA > 128 then --Wrap around HA exceeds size of the table.
               TempHA := TempHA - 128;
            end if;
            K := K + 1;
         end loop;
         Table(TempHA) := Insert;
      end if;
   end InsertRandom;
   
   --Finds and prints the Minimum, Maximum, and Average number of probes.
   procedure MinMaxAvg (Start: in Integer) is
      TTL : Integer := 0; --Total.
      AVG : Integer := 0; --Average.
      MAX : Integer := 0; --Maximum.
      MIN : Integer := 1; --Minimum.
      KeyNum : Integer := 30;
      K : Integer := 1;
      
   begin
      if Start /= 1 then
         K := Start;
         while KeyNum /= 0
         loop
            if Table(K).Key /= "&&&&&&&&&&&&&&&&" then
               
               TTL := TTL + Table(K).Probes; --Total number of probes.
               
               if Table(K).Probes < MIN then
                  MIN := Table(K).Probes; --Minimum number of probes.
               end if;
               
               if Table(K).Probes > MAX then
                  MAX := Table(K).Probes; --Max number of probes.
               end if;
               
               K := K - 1;
               KeyNum := KeyNum - 1;
               
            else
               K := K - 1;
            end if;
         end loop;
         
      else
         while KeyNum /= 0
         loop
            if Table(K).Key /= "&&&&&&&&&&&&&&&&" then
               
               TTL := TTL + Table(K).Probes; --Total number of probes.
               
               if Table(K).Probes < MIN then
                  MIN := Table(K).Probes; --Minimum number of probes.
               end if;
               
               if Table(K).Probes > MAX then
                  MAX := Table(K).Probes; --Max number of probes.
               end if;
               
               K := K + 1;
               KeyNum := KeyNum - 1;
               
            else
               K := K + 1;
            end if;
         end loop;
      end if;   
      
      AVG := (TTL / 30);
      put("Minimum number of probes for the first, or last, 30 keys: ");
      put(MIN, 0);
      New_Line(1);
      put("Maximum number of probes for the first, or last, 30 keys: ");
      put(MAX, 0);
      New_Line(1);
      put("Average number of probes for the first, or last, 30 keys: ");
      put(AVG, 0);
      New_Line(1);
      
   end MinMaxAvg;
   
   --Calculate the theoretical expected number of Linear probes.
   --DS notes page 157.
   procedure TheoreticalLinear (X: in Float) is
      alpha : Float := (X / Float(128)); --alpha = (number keys in the table) / (table size).
      Sum : Float;
      
   begin
      
      Sum := ((1.0 - alpha / 2.0) / (1.0 - alpha)); --E = (1-alpha/2)/(1-alpha).
      put("Theoretical expected number of probes to locate a random item: ");
      put(Sum);
   end TheoreticalLinear;
   
   --Calculate the theoretical expected number of Random probes.
   --DS notes page 159.
   procedure TheoreticalRandom (X: in Float) is
      alpha : Float := (X / Float(128)); --alpha = (number keys in the table) / (table size).
      Sum : Float;
      
   begin
      
      Sum := (-(1.0 / alpha) * Log(1.0 - alpha)); --E = -(1/alpha) log(1-alpha).
      put("Theoretical expected number of probes to locate a random item: ");
      put(Sum);
      
   end TheoreticalRandom;
   
   --Creates table with X percentage full.
   procedure Fill (X: Integer; LinearRandom: Integer) is 
      PtV : Integer;
   begin
      PtV := (128 * X / 100);
      --Opens "Words200D16.txt" file.
      Open(File => InputFile,
           Mode => In_File,
           Name => "Words200D16.txt");
      
      for K in 1..PtV
      loop
         declare
            InData : InputData;
         begin
            TempKey := Get_Line(InputFile);
            InData.Key := TempKey;
            InData.HA := BurrisHash(TempKey);
            if LinearRandom = 1 then --Linear approach.
               InsertLinear(InData.HA, InData);
            elsif LinearRandom = 2 then --Random approach.
               InsertRandom(InData.HA, InData);
            end if;
         end;
      end loop;
      
      --Closes "Words200D16.txt" file.
      Close(File => InputFile);
            
      --Checks if InputFile is already open and closes it if it is.
   exception
      when End_Error =>
         if Is_Open(File => InputFile) then
            Close(File => InputFile);
         end if;
      
   end Fill;   
   
begin
   --50% Linear.
   put("Linear hash for a 50% full table");
   New_Line(2);
   Fill(50, 1);
   MinMaxAvg(1);
   New_Line(1);
   MinMaxAvg(128);
   New_Line(1);
   TheoreticalLinear(64.0);
   New_Line(2);
   Display;
   Put("------------------------------------------------------");
   New_Line(1);
   
   Empty;
   
   --50% Random.
   put("Random hash for a 50% full table");
   New_Line(2);
   Fill(50, 2);
   MinMaxAvg(1);
   New_Line(1);
   MinMaxAvg(128);
   New_Line(1);
   TheoreticalRandom(64.0);
   New_Line(2);
   Display;
   Put("------------------------------------------------------");
   New_Line(1);
   
   Empty;
   
   --90% Linear.
   put("Linear hash for a 90% full table");
   New_Line(2);
   Fill(90, 1);
   MinMaxAvg(1);
   New_Line(1);
   MinMaxAvg(128);
   New_Line(1);
   TheoreticalLinear(115.0);
   New_Line(2);
   Display;
   Put("------------------------------------------------------");
   New_Line(1);
   
   Empty;
   
   --90% Random.
   put("Random hash for a 90% full table");
   New_Line(2);
   Fill(90, 2);
   MinMaxAvg(1);
   New_Line(1);
   MinMaxAvg(128);
   New_Line(1);
   TheoreticalRandom(115.0);
   New_Line(2);
   Display;
   Put("------------------------------------------------------");
   New_Line(1);
   
end Main;
