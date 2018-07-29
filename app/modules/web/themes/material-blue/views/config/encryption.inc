<?php
/**
 * @var $icons      \SP\Core\UI\ThemeIcons
 * @var $configData \SP\Config\ConfigData
 */ ?>

<form method="post" name="frmCrypt" id="frmCrypt" class="form-action"
      data-onsubmit="config/save"
      data-action-route="configEncryption/save"
      data-hash="">

    <div id="title" class="titleNormal">
        <i class="material-icons">enhanced_encryption</i>
        <?php echo __('Clave Maestra'); ?>
    </div>

    <table class="data tblConfig round">
        <?php if ($lastUpdateMPass > 0): ?>
            <tr>
                <td class="descField">
                    <?php echo __('Último cambio'); ?>
                </td>
                <td class="valField">
                    <div class="lowres-title"><?php echo __('Último cambio'); ?></div>

                    <?php echo date('r', $lastUpdateMPass); ?>
                </td>
            </tr>
        <?php endif; ?>
        <tr>
            <td class="descField">
                <?php echo __('Clave Maestra actual'); ?>
            </td>
            <td class="valField">
                <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                    <input id="current_masterpass" name="current_masterpass" type="password"
                           class="mdl-textfield__input mdl-color-text--indigo-400 passwordfield__input-show"
                           maxlength="255" required/>
                    <label class="mdl-textfield__label"
                           for="current_masterpass"><?php echo __('Clave Maestra actual'); ?></label>
                </div>
            </td>
        </tr>
        <tr>
            <td class="descField">
                <?php echo __('Nueva Clave Maestra'); ?>
            </td>
            <td class="valField">
                <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                    <input id="new_masterpass" name="new_masterpass" type="password"
                           class="mdl-textfield__input mdl-color-text--indigo-400 passwordfield__input"
                           maxlength="255" required/>
                    <label class="mdl-textfield__label"
                           for="new_masterpass"><?php echo __('Nueva Clave Maestra'); ?></label>
                </div>
            </td>
        </tr>
        <tr>
            <td class="descField">
                <?php echo __('Nueva Clave Maestra (repetir)'); ?>
            </td>
            <td class="valField">
                <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                    <input id="new_masterpass_repeat" name="new_masterpass_repeat" type="password"
                           class="mdl-textfield__input mdl-color-text--indigo-400"
                           maxlength="255" required/>
                    <label class="mdl-textfield__label"
                           for="new_masterpass_repeat"><?php echo __('Nueva Clave Maestra (repetir)'); ?></label>
                </div>
            </td>
        </tr>
        <tr>
            <td class="descField"></td>
            <td class="valField">
                <div
                        class="icon material-icons <?php echo $icons->getIconWarning()->getClass(); ?>"><?php echo $icons->getIconWarning()->getIcon(); ?></div>
                <?php echo __('Guarde la nueva clave en un lugar seguro.'); ?>
                <br>
                <div
                        class="icon material-icons <?php echo $icons->getIconWarning()->getClass(); ?>"><?php echo $icons->getIconWarning()->getIcon(); ?></div>
                <?php echo __('Se volverán a encriptar las claves de todas las cuentas.'); ?>
                <br>
                <div
                        class="icon material-icons <?php echo $icons->getIconWarning()->getClass(); ?>"><?php echo $icons->getIconWarning()->getIcon(); ?></div>
                <?php echo __('Los usuarios deberán de introducir la nueva clave maestra.'); ?>
                <br>
                <div
                        class="icon material-icons <?php echo $icons->getIconWarning()->getClass(); ?>"><?php echo $icons->getIconWarning()->getIcon(); ?></div>
                <strong><?php printf(__('Se van a actualizar %s cuentas. Este proceso puede tardar algo de tiempo.'), $numAccounts); ?></strong>
            </td>
        </tr>
        <tr>
            <td class="descField"></td>
            <td class="valField">
                <ul class="config-masterpass-list-action mdl-list">
                    <li class="mdl-list__item mdl-list__item--two-line">
                        <div class="mdl-switch__box">
                            <label class="mdl-switch mdl-js-switch mdl-js-ripple-effect" for="no_account_change">
                                <input type="checkbox" id="no_account_change"
                                       class="mdl-switch__input"
                                       name="no_account_change"/>
                            </label>
                        </div>

                        <span class="mdl-list__item-primary-content">
                            <span><?php echo __('No modificar cuentas'); ?></span>
                            <span class="mdl-list__item-sub-title">
                                <?php echo __('Establece una nueva clave maestra sin re-encriptar las cuentas'); ?>
                            </span>
                        </span>
                    </li>

                    <li class="mdl-list__item mdl-list__item--two-line">
                        <div class="mdl-switch__box">
                            <label class="mdl-switch mdl-js-switch mdl-js-ripple-effect"
                                   for="confirm_masterpass_change">
                                <input type="checkbox" id="confirm_masterpass_change"
                                       class="mdl-switch__input"
                                       name="confirm_masterpass_change"/>
                            </label>
                        </div>

                        <span class="mdl-list__item-primary-content">
                            <span><?php echo __('Confirmar cambio'); ?></span>
                            <span class="mdl-list__item-sub-title">
                                <?php echo __('Confirmar el cambio de clave maestra después de haber leído las advertencias anteriores.'); ?>
                            </span>
                        </span>
                    </li>
                </ul>
            </td>
        </tr>
    </table>

    <?php if (isset($taskId)): ?>
        <input type="hidden" name="taskId" value="<?php echo $taskId; ?>">
        <input type="hidden" name="lock" value="masterpass">
    <?php endif; ?>
</form>
<div class="tab-actions">
    <ul>
        <li>
            <button id="help_mpass_button" type="button"
                    class="btn-help mdl-button mdl-js-button mdl-button--fab mdl-button--mini-fab mdl-button--colored"
                    title="<?php echo $icons->getIconHelp()->getTitle(); ?>"
                    data-help="help-mpass">
                <i class="material-icons"><?php echo $icons->getIconHelp()->getIcon(); ?></i>
            </button>

            <div for="help-mpass" class="help-box" title="<?php echo __('Clave Maestra'); ?>">
                <div class="help-container">
                    <p class="help-text"><?php echo __('La clave maestra es utilizada para encriptar las claves de las cuentas de sysPass para mantenerlas seguras.'); ?></p>

                    <p class="help-text"><?php echo __('Es recomendable cambiarla cada cierto tiempo y utilizar una clave compleja que incluya números, letras y símbolos.'); ?></p>

                    <p class="help-text"><?php printf(__('Para más información consulte: %s'), '<a target="_blank" href="https://doc.syspass.org">https://doc.syspass.org</a>'); ?></p>
                </div>
            </div>
        </li>
        <?php if ($userIsAdminApp): ?>
            <li>
                <button type="button"
                        class="btn-action mdl-button mdl-js-button mdl-button--fab mdl-button--mini-fab mdl-button--colored <?php echo $icons->getIconCheck()->getClassButton(); ?>"
                        data-onclick="config/refreshMpass"
                        data-action-route="configEncryption/refresh"
                        title="<?php echo __('Actualizar hash de clave maestra'); ?>">
                    <i class="material-icons"><?php echo $icons->getIconRefresh()->getIcon(); ?></i>
                </button>
            </li>
        <?php endif; ?>

        <?php if ($numAccounts > 0): ?>
            <li>
                <button form="frmCrypt"
                        class="mdl-button mdl-js-button mdl-button--fab mdl-button--mini-fab mdl-button--colored <?php echo $icons->getIconPlay()->getClassButton(); ?>"
                        title="<?php echo $icons->getIconPlay()->getTitle(); ?>">
                    <i class="material-icons"><?php echo $icons->getIconPlay()->getIcon(); ?></i>
                </button>
            </li>
        <?php endif; ?>
    </ul>
</div>

<div id="title" class="titleNormal">
    <i class="material-icons">enhanced_encryption</i>
    <?php echo __('Clave Temporal'); ?>
</div>

<form method="post" name="frmTempMasterPass" id="frmTempMasterPass" class="form-action"
      data-onsubmit="config/save"
      data-action-route="configEncryption/saveTemp">
    <table class="data tblConfig">
        <tr>
            <td class="descField">
                <?php echo __('Último cambio'); ?>
            </td>
            <td class="valField">
                <div class="lowres-title"><?php echo __('Último cambio'); ?></div>

                <?php echo ($tempMasterPassTime > 0) ? date('r', $tempMasterPassTime) : __('No generada'); ?>
            </td>
        </tr>
        <tr>
            <td class="descField">
                <?php echo __('Válido hasta'); ?>
            </td>
            <td class="valField">
                <div class="lowres-title"><?php echo __('Válido hasta'); ?></div>

                <?php if (time() > $tempMasterMaxTime): ?>
                    <span style="color: red"><?php echo date('r', $tempMasterMaxTime); ?></span>
                <?php elseif ($tempMasterMaxTime > 0): echo date('r', $tempMasterMaxTime); ?>
                <?php else: echo __('No generada'); ?>
                <?php endif; ?>
            </td>
        </tr>
        <tr>
            <td class="descField">
                <?php echo __('Intentos'); ?>
            </td>
            <td class="valField">
                <div class="lowres-title"><?php echo __('Intentos'); ?></div>

                <?php echo $tempMasterAttempts; ?>
            </td>
        </tr>
        <tr>
            <td class="descField">
                <?php echo __('Validez (s)'); ?>
            </td>
            <td class="valField">
                <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                    <input id="temporary_masterpass_maxtime" name="temporary_masterpass_maxtime" type="number"
                           step="600"
                           pattern="[0-9]{2,6}" class="mdl-textfield__input mdl-color-text--indigo-400"
                           value="3600"
                           required/>
                    <label class="mdl-textfield__label"
                           for="temporary_masterpass_maxtime"><?php echo __('Validez (s)'); ?></label>
                </div>
            </td>
        </tr>
        <tr>
            <td class="descField"></td>
            <td class="valField">
                <ul class="config-masterpass-list-action mdl-list">
                    <li class="mdl-list__item mdl-list__item--two-line">
                        <div class="mdl-switch__box">
                            <label class="mdl-switch mdl-js-switch mdl-js-ripple-effect"
                                   for="temporary_masterpass_email">
                                <input type="checkbox" id="temporary_masterpass_email"
                                       class="mdl-switch__input"
                                       name="temporary_masterpass_email" <?php echo !$configData->isMailEnabled() ? 'disabled' : ''; ?>/>
                            </label>
                        </div>

                        <span class="mdl-list__item-primary-content">
                            <span><?php echo __('Enviar correo'); ?></span>
                            <span class="mdl-list__item-sub-title">
                                <?php echo __('Envía un correo a todos los usuarios o sólo a los del grupo seleccionado.'); ?>
                            </span>
                        </span>
                    </li>
                </ul>
            </td>
        </tr>
        <tr>
            <td class="descField">
                <?php echo __('Grupo'); ?>
            </td>
            <td class="valField">
                <div class="lowres-title"><?php echo __('Grupo'); ?></div>

                <select id="temporary_masterpass_group" name="temporary_masterpass_group"
                        class="select-box select-box-deselect" <?php echo !$configData->isMailEnabled() ? 'disabled' : ''; ?>>
                    <option value=""><?php echo __('Seleccionar Grupo'); ?></option>
                    <?php /** @var \SP\Mvc\View\Components\SelectItem[] $userGroups */
                    foreach ($userGroups as $userGroup): ?>
                        <option
                                value="<?php echo $userGroup->getId(); ?>"><?php echo $userGroup->getName(); ?></option>
                    <?php endforeach; ?>
                </select>
            </td>
        </tr>
        <?php if (!empty($tempMasterPass)): ?>
            <tr>
                <td class="descField">
                    <?php echo __('Clave'); ?>
                </td>
                <td class="valField">
                    <div class="lowres-title"><?php echo __('Clave'); ?></div>

                    <?php echo $tempMasterPass; ?>
                </td>
            </tr>
        <?php endif; ?>
    </table>
</form>

<div class="tab-actions">
    <ul>
        <li>
            <button id="btnBack" type="button"
                    class="btn-back mdl-button mdl-js-button mdl-button--fab mdl-button--mini-fab mdl-button--colored <?php echo $icons->getIconBack()->getClassButton(); ?>"
                    title="<?php echo __('Atrás'); ?>">
                <i class="material-icons"><?php echo $icons->getIconBack()->getIcon(); ?></i>
            </button>
        </li>
        <li>
            <button id="help_tmpass_button"
                    class="btn-help mdl-button mdl-js-button mdl-button--fab mdl-button--mini-fab mdl-button--colored"
                    title="<?php echo $icons->getIconHelp()->getTitle(); ?>"
                    data-help="help-tmpass">
                <i class="material-icons"><?php echo $icons->getIconHelp()->getIcon(); ?></i>
            </button>


            <div for="help-tmpass" class="help-box" title="<?php echo __('Clave Temporal'); ?>">
                <div class="help-container">
                    <p class="help-text"><?php echo __('La clave temporal es utilizada como clave maestra para los usuarios que necesitan introducirla al iniciar la sesión, así no es necesario facilitar la clave maestra original.'); ?></p>
                </div>
            </div>
        </li>
        <li>
            <button form="frmTempMasterPass"
                    class="mdl-button mdl-js-button mdl-button--fab mdl-button--mini-fab mdl-button--colored <?php echo $icons->getIconPlay()->getClassButton(); ?>"
                    title="<?php echo __('Generar'); ?>">
                <i class="material-icons"><?php echo $icons->getIconPlay()->getIcon(); ?></i>
            </button>
        </li>
    </ul>
</div>