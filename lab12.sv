/*-======================================================================
-- Description: generate a 3-level test bar pattern:
--   * gray scale 
--   * 8 prime colors
--   * a continuous color spectrum
--   * it is customized for 12-bit VGA
--   * two registers form 2-clock delay line  
--======================================================================*/

module bar_demo 
   (
    input  logic [10:0] x, y,     // treated as x-/y-axis
    input  logic [1:0] size,
    input  logic [11:0] color,
    output logic [11:0] bar_rgb 
   );

   // declaration
   logic [3:0] r, g, b;
   
   always_comb
   begin
      // 16 shades of gray
      if (size == 2'b11) begin
        if(y > 240 - 64 && y < 240 + 64 && x > 320 - 64 && x < 320 + 64) begin
             r = color[3:0];
             g = color[7:4];
             b = color[11:8]; 
         end
         else begin
             r = 4'b1111 - color[3:0];
             g = 4'b1111 - color[7:4];
             b = 4'b1111 - color[11:8]; 
         end
      end 
      else if(size == 2'b10) begin
         if(y > 240 - 32 && y < 240 + 32 && x > 320 - 32 && x < 320 + 32) begin
             r = color[3:0];
             g = color[7:4];
             b = color[11:8]; 
         end
         else begin
             r = 4'b1111 - color[3:0];
             g = 4'b1111 - color[7:4];
             b = 4'b1111 - color[11:8]; 
         end
      end 
      else if(size == 2'b01) begin
         if(y > 240 - 16 && y < 240 + 16 && x > 320 - 16 && x < 320 + 16) begin
             r = color[3:0];
             g = color[7:4];
             b = color[11:8]; 
         end
         else begin
             r = 4'b1111 - color[3:0];
             g = 4'b1111 - color[7:4];
             b = 4'b1111 - color[11:8]; 
         end
      end 
      else if(size == 2'b00) begin
         if(y > 240 - 8 && y < 240 + 8 && x > 320 - 8 && x < 320 + 8) begin
             r = color[3:0];
             g = color[7:4];
             b = color[11:8]; 
         end
         else begin
             r = 4'b1111 - color[3:0];
             g = 4'b1111 - color[7:4];
             b = 4'b1111 - color[11:8]; 
         end
      end 
   end // always   
   // output
   assign bar_rgb = {r, g, b};
endmodule
