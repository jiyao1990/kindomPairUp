<GameProjectFile>
  <PropertyGroup Type="Scene" Name="GameScene" ID="0fb4353b-941a-4976-a031-d73516ee1ca8" Version="2.0.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1" />
      <ObjectData Name="Scene" CanEdit="False" FrameEvent="" ctype="SingleNodeObjectData">
        <Position X="0" Y="0" />
        <Scale ScaleX="1" ScaleY="1" />
        <AnchorPoint />
        <CColor A="255" R="255" G="255" B="255" />
        <Size X="640" Y="960" />
        <PrePosition X="0" Y="0" />
        <PreSize X="0" Y="0" />
        <Children>
          <NodeObjectData Name="bgLayer" ActionTag="11" FrameEvent="" Tag="9" ObjectIndex="1" PrePositionEnabled="True" PreSizeEnable="True" ComboBoxIndex="1" ColorAngle="90" ctype="PanelObjectData">
            <Position X="320" Y="0" />
            <Scale ScaleX="1" ScaleY="1" />
            <AnchorPoint ScaleX="0.5" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="640" Y="960" />
            <PrePosition X="0.5" Y="0" />
            <PreSize X="1" Y="1" />
            <Children>
              <NodeObjectData Name="boxBg" ActionTag="12" FrameEvent="" Tag="10" ObjectIndex="1" PrePositionEnabled="True" ctype="SpriteObjectData">
                <Position X="320" Y="0" />
                <Scale ScaleX="1" ScaleY="1" />
                <AnchorPoint ScaleX="0.5" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="640" Y="644" />
                <PrePosition X="0.5" Y="0" />
                <PreSize X="0" Y="0" />
                <Children>
                  <NodeObjectData Name="box" ActionTag="13" FrameEvent="" Tag="11" ObjectIndex="2" PrePositionEnabled="True" ctype="SpriteObjectData">
                    <Position X="320" Y="644" />
                    <Scale ScaleX="1" ScaleY="1" />
                    <AnchorPoint ScaleX="0.5" ScaleY="1" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <Size X="627" Y="639" />
                    <PrePosition X="0.5" Y="1" />
                    <PreSize X="0" Y="0" />
                    <FileData Type="Normal" Path="iphone/ui/box.png" />
                  </NodeObjectData>
                  <NodeObjectData Name="grass" ActionTag="15" FrameEvent="" Tag="13" ObjectIndex="4" PrePositionEnabled="True" ctype="SpriteObjectData">
                    <Position X="320" Y="644" />
                    <Scale ScaleX="1" ScaleY="1" />
                    <AnchorPoint ScaleX="0.5" ScaleY="0.5" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <Size X="640" Y="92" />
                    <PrePosition X="0.5" Y="1" />
                    <PreSize X="0" Y="0" />
                    <Children>
                      <NodeObjectData Name="field" ActionTag="16" FrameEvent="" Tag="14" ObjectIndex="5" PrePositionEnabled="True" ctype="SpriteObjectData">
                        <Position X="320" Y="46" />
                        <Scale ScaleX="1" ScaleY="1" />
                        <AnchorPoint ScaleX="0.5" ScaleY="0.5" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <Size X="594" Y="46" />
                        <PrePosition X="0.5" Y="0.5" />
                        <PreSize X="0" Y="0" />
                        <FileData Type="Normal" Path="iphone/ui/field.png" />
                      </NodeObjectData>
                    </Children>
                    <FileData Type="Normal" Path="iphone/ui/grass.png" />
                  </NodeObjectData>
                </Children>
                <FileData Type="Normal" Path="iphone/ui/box_bg.png" />
              </NodeObjectData>
            </Children>
            <SingleColor A="255" R="184" G="244" B="255" />
            <FirstColor A="255" R="184" G="244" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1" />
          </NodeObjectData>
          <NodeObjectData Name="pauseBg" ActionTag="18" FrameEvent="" Tag="16" ObjectIndex="7" PrePositionEnabled="True" ctype="SpriteObjectData">
            <Position X="640" Y="960" />
            <Scale ScaleX="1" ScaleY="1" />
            <AnchorPoint ScaleX="1" ScaleY="1" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="108" Y="103" />
            <PrePosition X="1" Y="1" />
            <PreSize X="0" Y="0" />
            <Children>
              <NodeObjectData Name="btn_pause" ActionTag="19" FrameEvent="" Tag="17" ObjectIndex="1" PrePositionEnabled="True" TouchEnable="True" FontSize="14" ButtonText="" Scale9Width="50" Scale9Height="55" ctype="ButtonObjectData">
                <Position X="64.8" Y="51.5" />
                <Scale ScaleX="1" ScaleY="1" />
                <AnchorPoint ScaleX="0.5" ScaleY="0.5" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="50" Y="55" />
                <PrePosition X="0.6" Y="0.5" />
                <PreSize X="0" Y="0" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Normal" Path="iphone/ui/pause_up.png" />
                <PressedFileData Type="Normal" Path="iphone/ui/pause_down.png" />
                <NormalFileData Type="Normal" Path="iphone/ui/pause_up.png" />
              </NodeObjectData>
            </Children>
            <FileData Type="Normal" Path="iphone/ui/pause_bg.png" />
          </NodeObjectData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>