<?php
/**
 * sysPass
 *
 * @author    nuxsmin
 * @link      https://syspass.org
 * @copyright 2012-2018, Rubén Domínguez nuxsmin@$syspass.org
 *
 * This file is part of sysPass.
 *
 * sysPass is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * sysPass is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *  along with sysPass.  If not, see <http://www.gnu.org/licenses/>.
 */

namespace SP\Modules\Web\Controllers;

use SP\Core\Acl\Acl;
use SP\Core\Events\Event;
use SP\DataModel\ItemSearchData;
use SP\Modules\Web\Controllers\Helpers\ItemsGridHelper;
use SP\Modules\Web\Controllers\Helpers\TabsGridHelper;
use SP\Services\AuthToken\AuthTokenService;
use SP\Services\PublicLink\PublicLinkService;
use SP\Services\User\UserService;
use SP\Services\UserGroup\UserGroupService;
use SP\Services\UserProfile\UserProfileService;

/**
 * Class AccessMgmtController
 *
 * @package SP\Modules\Web\Controllers
 */
final class AccessManagerController extends ControllerBase
{
    /**
     * @var ItemSearchData
     */
    protected $itemSearchData;
    /**
     * @var ItemsGridHelper
     */
    protected $itemsGridHelper;
    /**
     * @var TabsGridHelper
     */
    protected $tabsGridHelper;

    /**
     * @throws \SP\Core\Exceptions\ConstraintException
     * @throws \SP\Core\Exceptions\QueryException
     */
    public function indexAction()
    {
        $this->getGridTabs();
    }

    /**
     * Returns a tabbed grid with items
     *
     * @throws \SP\Core\Exceptions\ConstraintException
     * @throws \SP\Core\Exceptions\QueryException
     */
    protected function getGridTabs()
    {
        $this->itemSearchData = new ItemSearchData();
        $this->itemSearchData->setLimitCount($this->configData->getAccountCount());

        $this->itemsGridHelper = $this->dic->get(ItemsGridHelper::class);
        $this->tabsGridHelper = $this->dic->get(TabsGridHelper::class);

        $this->itemsGridHelper->setQueryTimeStart(microtime(true));

        if ($this->checkAccess(Acl::USER)) {
            $this->tabsGridHelper->addTab($this->getUsersList());
        }

        if ($this->checkAccess(Acl::GROUP)) {
            $this->tabsGridHelper->addTab($this->getUsersGroupList());
        }

        if ($this->checkAccess(Acl::PROFILE)) {
            $this->tabsGridHelper->addTab($this->getUsersProfileList());
        }

        if ($this->checkAccess(Acl::AUTHTOKEN)) {
            $this->tabsGridHelper->addTab($this->getApiTokensList());
        }

        if ($this->configData->isPublinksEnabled() && $this->checkAccess(Acl::PUBLICLINK)) {
            $this->tabsGridHelper->addTab($this->getPublicLinksList());
        }

        $this->eventDispatcher->notifyEvent('show.itemlist.accesses', new Event($this));

        $this->tabsGridHelper->renderTabs(Acl::getActionRoute(Acl::ACCESS_MANAGE), $this->request->analyzeInt('tabIndex', 0));

        $this->view();
    }

    /**
     * Returns users' data tab
     *
     * @return \SP\Html\DataGrid\DataGridTab
     * @throws \SP\Core\Exceptions\ConstraintException
     * @throws \SP\Core\Exceptions\QueryException
     */
    protected function getUsersList()
    {

        return $this->itemsGridHelper->getUsersGrid($this->dic->get(UserService::class)->search($this->itemSearchData))->updatePager();
    }

    /**
     * Returns users group data tab
     *
     * @return \SP\Html\DataGrid\DataGridTab
     * @throws \SP\Core\Exceptions\ConstraintException
     * @throws \SP\Core\Exceptions\QueryException
     */
    protected function getUsersGroupList()
    {
        return $this->itemsGridHelper->getUserGroupsGrid($this->dic->get(UserGroupService::class)->search($this->itemSearchData))->updatePager();
    }

    /**
     * Returns users profile data tab
     *
     * @return \SP\Html\DataGrid\DataGridTab
     * @throws \SP\Core\Exceptions\ConstraintException
     * @throws \SP\Core\Exceptions\QueryException
     */
    protected function getUsersProfileList()
    {
        return $this->itemsGridHelper->getUserProfilesGrid($this->dic->get(UserProfileService::class)->search($this->itemSearchData))->updatePager();
    }

    /**
     * Returns API tokens data tab
     *
     * @return \SP\Html\DataGrid\DataGridTab
     * @throws \SP\Core\Exceptions\ConstraintException
     * @throws \SP\Core\Exceptions\QueryException
     */
    protected function getApiTokensList()
    {
        return $this->itemsGridHelper->getAuthTokensGrid($this->dic->get(AuthTokenService::class)->search($this->itemSearchData))->updatePager();
    }

    /**
     * Returns public links data tab
     *
     * @return \SP\Html\DataGrid\DataGridTab
     * @throws \SP\Core\Exceptions\ConstraintException
     * @throws \SP\Core\Exceptions\QueryException
     */
    protected function getPublicLinksList()
    {
        return $this->itemsGridHelper->getPublicLinksGrid($this->dic->get(PublicLinkService::class)->search($this->itemSearchData))->updatePager();
    }

    /**
     * @return TabsGridHelper
     */
    public function getTabsGridHelper()
    {
        return $this->tabsGridHelper;
    }

    /**
     * @throws \Psr\Container\ContainerExceptionInterface
     * @throws \Psr\Container\NotFoundExceptionInterface
     * @throws \SP\Services\Auth\AuthException
     */
    protected function initialize()
    {
        $this->checkLoggedIn();
    }
}