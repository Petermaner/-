--1位半加器描述
library ieee;
use ieee.std_logic_1164.all;
entity h_adder is port(
	a,b : in std_logic;
	co,so : out std_logic);
end h_adder;
architecture one of h_adder is
begin
co<=not(a nand b);
so<=(a or b) and (a nand b);
end one;

--或门描述
library ieee;
use ieee.std_logic_1164.all;
entity myor2 is port(
	a,b : in std_logic;
	y : out std_logic);
end myor2;
architecture one of myor2 is
begin
y<=a or b;
end one;


--1位全加器描述
library ieee;
use ieee.std_logic_1164.all;
entity f_adder is port(
	ain,bin,cin : in std_logic;
	sum,cout : out std_logic);
end f_adder;
architecture one of f_adder is
component h_adder port(
	a,b : in std_logic;
	co,so : out std_logic);
end component;

component myor2 port(
	a,b : in std_logic;
	y : out std_logic);
end component;

signal d,e,f : std_logic;
begin
u1 : h_adder port map(a=>ain,b=>bin,co=>d,so=>e);
u2 : h_adder port map(a=>e,b=>cin,co=>f,so=>sum);
u3 : myor2 port map(a=>d,b=>f,y=>cout);
end one;

	
	
library ieee;
use ieee.std_logic_1164.all;
entity mux21 is
	port(A,B,S:in std_logic;
	    Y:out std_logic);
end entity mux21;
architecture one of mux21 is
	signal temp1,temp2:std_logic;
begin
	temp1<=A and S;
	temp2=(not B) nand S;
        Y=temp1 or temp2;
end architecture one;         
