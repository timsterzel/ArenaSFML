<?xml version="1.0" encoding="UTF-8"?>
<tileset name="scifi" tilewidth="32" tileheight="32" tilecount="6" columns="3">
 <image source="../sprites/tiles/level.png" width="96" height="64"/>
 <tile id="0" type="wall">
  <properties>
   <property name="collision" type="bool" value="true"/>
   <property name="identifier" value="wall_red"/>
  </properties>
 </tile>
 <tile id="1" type="wall">
  <properties>
   <property name="collision" type="bool" value="true"/>
   <property name="identifier" value="wall_blue"/>
  </properties>
 </tile>
 <tile id="2" type="ground">
  <properties>
   <property name="collision" type="bool" value="false"/>
   <property name="identifier" value="ground1"/>
  </properties>
 </tile>
 <tile id="3" type="door">
  <properties>
   <property name="collision" type="bool" value="true"/>
   <property name="identifier" value="door_vert_red"/>
  </properties>
 </tile>
 <tile id="4" type="door">
  <properties>
   <property name="collision" type="bool" value="true"/>
   <property name="identifier" value="door_vert_blue"/>
  </properties>
 </tile>
 <tile id="5" type="ground">
  <properties>
   <property name="collision" type="bool" value="false"/>
   <property name="identifier" value="ground2"/>
  </properties>
 </tile>
</tileset>
