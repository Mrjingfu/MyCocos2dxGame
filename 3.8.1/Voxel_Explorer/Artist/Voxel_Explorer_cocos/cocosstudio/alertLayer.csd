<GameProjectFile>
  <PropertyGroup Type="Layer" Name="alertLayer" ID="65ce497d-9a35-40e0-877c-eb5ffa6c8e73" Version="2.3.2.3" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Layer" Tag="10" ctype="GameLayerObjectData">
        <Size X="150.0000" Y="100.0000" />
        <Children>
          <AbstractNodeData Name="alert_layer_layout" ActionTag="-1763356122" Tag="11" IconVisible="False" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" HorizontalEdge="BothEdge" VerticalEdge="BothEdge" TouchEnable="True" BackColorAlpha="102" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Enable="True" LeftEage="5" RightEage="5" TopEage="5" BottomEage="5" ctype="PanelObjectData">
            <Size X="150.0000" Y="100.0000" />
            <Children>
              <AbstractNodeData Name="alert_layer_title_img" ActionTag="62396566" Tag="20" IconVisible="False" HorizontalEdge="BothEdge" VerticalEdge="BothEdge" LeftMargin="40.0000" RightMargin="40.0000" TopMargin="-10.0000" BottomMargin="90.0000" Scale9Enable="True" LeftEage="5" RightEage="5" TopEage="5" BottomEage="5" Scale9OriginX="5" Scale9OriginY="5" Scale9Width="4" Scale9Height="4" ctype="ImageViewObjectData">
                <Size X="70.0000" Y="20.0000" />
                <Children>
                  <AbstractNodeData Name="alert_layer_title_text" ActionTag="-1076168566" Tag="23" IconVisible="False" HorizontalEdge="BothEdge" VerticalEdge="BothEdge" LeftMargin="-20.5000" RightMargin="-20.5000" TopMargin="-4.5000" BottomMargin="-4.5000" FontSize="36" LabelText="提示" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="72.0000" Y="42.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="35.0000" Y="10.0000" />
                    <Scale ScaleX="0.3000" ScaleY="0.3000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="75.0000" Y="100.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="1.0000" />
                <PreSize X="0.4667" Y="0.2000" />
                <FileData Type="PlistSubImage" Path="ui_frame_3.png" Plist="ui_sprite.plist" />
              </AbstractNodeData>
              <AbstractNodeData Name="alert_layer_ok" ActionTag="402936973" Tag="21" IconVisible="False" HorizontalEdge="BothEdge" VerticalEdge="BothEdge" LeftMargin="20.0000" RightMargin="80.0000" TopMargin="66.5000" BottomMargin="8.5000" TouchEnable="True" FontSize="14" ButtonText="确定" Scale9Enable="True" LeftEage="4" RightEage="4" TopEage="4" BottomEage="4" Scale9OriginX="4" Scale9OriginY="4" Scale9Width="5" Scale9Height="5" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="50.0000" Y="25.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="45.0000" Y="21.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.3000" Y="0.2100" />
                <PreSize X="0.3333" Y="0.2500" />
                <FontResource Type="Normal" Path="fonts/fangz.TTF" Plist="" />
                <TextColor A="255" R="255" G="255" B="255" />
                <NormalFileData Type="PlistSubImage" Path="ui_frame_6.png" Plist="ui_sprite.plist" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="alert_layer_cancel" ActionTag="-1377375493" Tag="25" IconVisible="False" HorizontalEdge="BothEdge" VerticalEdge="BothEdge" LeftMargin="80.0000" RightMargin="20.0000" TopMargin="66.5000" BottomMargin="8.5000" TouchEnable="True" FontSize="14" ButtonText="取消" Scale9Enable="True" LeftEage="4" RightEage="4" TopEage="4" BottomEage="4" Scale9OriginX="4" Scale9OriginY="4" Scale9Width="5" Scale9Height="5" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="50.0000" Y="25.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="105.0000" Y="21.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.7000" Y="0.2100" />
                <PreSize X="0.3333" Y="0.2500" />
                <FontResource Type="Normal" Path="fonts/fangz.TTF" Plist="" />
                <TextColor A="255" R="255" G="255" B="255" />
                <NormalFileData Type="PlistSubImage" Path="ui_frame_6.png" Plist="ui_sprite.plist" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="alert_layer_message" ActionTag="-592131196" Tag="24" IconVisible="False" HorizontalEdge="BothEdge" VerticalEdge="BothEdge" LeftMargin="-151.3937" RightMargin="-155.6063" TopMargin="-23.0956" BottomMargin="-5.9044" FontSize="36" LabelText="qqqqqqqqqqqqqqqqqqqqasd&#xA;" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="457.0000" Y="43.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="77.1063" Y="58.5956" />
                <Scale ScaleX="0.3000" ScaleY="0.3000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5140" Y="0.5860" />
                <PreSize X="1.9933" Y="0.4300" />
                <FontResource Type="Normal" Path="fonts/fangz.TTF" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="1.0000" Y="1.0000" />
            <FileData Type="PlistSubImage" Path="ui_frame_1.png" Plist="ui_sprite.plist" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>