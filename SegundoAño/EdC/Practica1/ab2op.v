module ab2op(output reg [3:0] Op1, Op2, input wire [3:0] A, B, input wire l, input wire [1:0] ALUOP);
  always@(A or B or l or ALUOP)
      begin
        if(l == 1'b1) 
          begin
            Op1 = A;
            Op2 = B;
          end
        else
          begin
            case(ALUOP)
              2'b00:
                begin
                  Op1 = 
                  Op2 = 
                end
              2'b01:
                begin
                  Op1 = 
                  Op2 =
                end
              2'b10:
                begin
                  Op1= 
                  Op2=
                end
              2'b11:
                begin
                  Op1=
                  Op2=
                end
            endcase
          end
      end
  
endmodule